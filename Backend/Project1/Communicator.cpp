#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
#include <future>

#define invalid_status(first_char) first_char != ROOM_CHAR and first_char != STATISTICS_CHAR and first_char != ADMIN_CHAR and first_char != MEMBER_CHAR and first_char != 7 and first_char != 8

void logBuffer(const Buffer& buffer) {
    std::cout << "status: " << std::to_string(buffer.status) << " size of data: " << buffer.sizeOfData;
    if (buffer.sizeOfData>0)
    {
        std::cout << " data: "<<std::string{buffer.data};
    }
    std::cout << std::endl;
}


Communicator::Communicator(int port, std::string ip) :_ipAddress(ip), _port(port), _socketAddress_len(sizeof(_socketAddress)), _socketAddress()
{
    if (startServer() != 1)
    {
        std::wcout << "Failed to start server with PORT: " << ntohs(_socketAddress.sin_port);
        
    }
    startListen();
}
inline int Communicator::startServer()
{
    PVOID pAddrBuf;
    if (WSAStartup(MAKEWORD(2, 0), &_wsaData) != 0)
    {
        exit(420);
    }

    _ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_ListenSocket < 0)
    {
        exit(420);
    }

    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_port = htons(_port);

    std::wstring widestr = std::wstring(_ipAddress.begin(), _ipAddress.end());
    const wchar_t* widecstr = widestr.c_str();

    InetPton(_socketAddress.sin_family, widecstr, &_socketAddress.sin_addr.s_addr);

    if (bind(_ListenSocket, (sockaddr*)&_socketAddress, _socketAddress_len) < 0)
    {
        exit(420);
    }

    return 1;
}

inline void Communicator::startListen()
{
    if (listen(_ListenSocket,20)<0)
    {
        exit(777);
    }
    std::cout << "listen binded"<<'\n';
    
}

void Communicator::startHandlingRequest()
{
    std::thread t(&Communicator::Handler, this);
    t.detach();
}

void Communicator::Handler()
{
    while (true)
    {
        SOCKET newSocket = accept(_ListenSocket, (sockaddr*)&_socketAddress, &_socketAddress_len);
        std::function<void()> handleConnectionFunction = [this, &newSocket]() {
            if (newSocket < 0)
            {

                PWSTR str = nullptr;
                InetNtop(_socketAddress.sin_family, &_socketAddress.sin_addr.s_addr, str, 50);
                exit(888);
            }
            /*TODO:
            * switch this with request factory
            */


            Buffer buffer = getBuffer(newSocket);
            IRequestHandler* handler = RequsetFactory::getInstence().getFirstRequsetHandler(buffer);
            _clients.emplace(newSocket, handler);
            Buffer responceBuffer;
            Responce* responce;
            while (handler!=nullptr)
            {
                
                //procees request
                
                try
                {
                   auto request = handler->GetRequestFromBuffer(buffer);
                   std::cout << "request: ";
                   logBuffer(buffer);
                   if (request==nullptr)
                   {
                       throw std::invalid_argument("invalid request");
                   }
                   responce = handler->HandlerRequest(request);
                   if (responce==nullptr)
                   {
                       throw std::invalid_argument("can processes request");
                   }
                    delete handler;
                    delete request;
                    handler = responce->next;
                    
                    //free memory
                    //delete request;

                    responceBuffer = responce->buffer;
                    std::pair<char*, int>& byteArray = getByteArrayFromBuffer(responceBuffer);
                    send(newSocket, byteArray.first, byteArray.second, 0);
                    std::cout << "my response: ";
                    logBuffer(responceBuffer);
                    if (responce->buffer.data != nullptr && *(responce->buffer.data) != '\0')
                    {
                        delete[] responce->buffer.data;
                        
                    }
                    
                }
                catch (const std::exception& e)
                {
                    http::json::JsonObject errorjson;
                    errorjson.insert({ "error",{e.what()} });
                    std::string jsonCache = errorjson.ToString();

                    responceBuffer.status = Error;
                    responceBuffer.sizeOfData = jsonCache.length();
                    responceBuffer.data = new char[jsonCache.length() + 1];
                    std::copy(jsonCache.begin(), jsonCache.end(), responceBuffer.data);
                    responceBuffer.data[jsonCache.size()] = '\0';

                    std::pair<char*, int>& byteArray = getByteArrayFromBuffer(responceBuffer);

                    send(newSocket, byteArray.first, byteArray.second, 0);
                    handler = nullptr;
                    std::cout << "my response: ";
                    logBuffer(responceBuffer);
                }
                catch (...)
                {
                    http::json::JsonObject errorjson;
                    errorjson.insert({ "error",{"had an internal error soz UwU"}});
                    std::string jsonCache = errorjson.ToString();

                    responceBuffer.status = Error;
                    responceBuffer.sizeOfData = jsonCache.length();
                    responceBuffer.data = new char[jsonCache.length()+1];
                    std::copy(jsonCache.begin(), jsonCache.end(), responceBuffer.data);
                    responceBuffer.data[jsonCache.size()] = '\0';

                    std::pair<char*, int>& byteArray = getByteArrayFromBuffer(responceBuffer);

                    send(newSocket, byteArray.first, byteArray.second, 0);
                    handler = nullptr;
                    std::cout << "my response: ";
                    logBuffer(responceBuffer);
                }

                if (handler!=nullptr)
                {
                    buffer = getBuffer(newSocket);
                }
            }
            _clients.erase(newSocket);
            closesocket(newSocket);
        };
        std::thread thread(handleConnectionFunction);
        thread.detach();
    }
}

std::pair<char*, int>& Communicator::getByteArrayFromBuffer(const Buffer& buffer) const
{
    int size = sizeOfStatusInHeader + sizeOfDataLengthInHeader + buffer.sizeOfData;
    
    
    char* formattedData = new char[size];
    
    
    formattedData[0] = buffer.status;

    
    std::memcpy(formattedData + sizeOfStatusInHeader, &buffer.sizeOfData, sizeOfDataLengthInHeader);

    
    if (buffer.data != nullptr && *(buffer.data) != '\0')
    {
        std::memcpy(formattedData + sizeOfStatusInHeader + sizeOfDataLengthInHeader, buffer.data, buffer.sizeOfData);
    }
    else
    {
        formattedData[size - 1] = '\0';
    }

    
    std::pair<char*, int> result(formattedData, size);

    
    return result;
}

     

Buffer Communicator::getBuffer(SOCKET socket) const
{
    // Define buffer struct
    Buffer buffer;

    // Read status byte from socket
    readBuffer:
    int bytesReceived = recv(socket, (char*)&buffer.status, sizeof(buffer.status), 0);
    if (bytesReceived != sizeof(buffer.status))
    {
        int error = WSAGetLastError();
        std::cout << "error in getting status num " << error << std::endl;
        return Buffer{ .status = 1 }; //we have no status named 1 witch means the next handler to take it will fail and throw an error

    }
    try
    {
        char first_char = std::to_string(buffer.status)[0];
        if (first_char != ROOM_CHAR && first_char != STATISTICS_CHAR && first_char != ADMIN_CHAR && first_char != MEMBER_CHAR && first_char != '7' && first_char != '8' && first_char!=QUESTION_CHAR)
        {
            if (first_char=='\0')
            {
                goto readBuffer;
            }
            int error = WSAGetLastError();
            return Buffer{ .status = 1 }; //we have no status named 1 witch means the next handler to take it will fail and throw an error
        }
    }
    catch (...)
    {
        throw;
    }
    // Read size of data (4 bytes) from socket
    bytesReceived = recv(socket, (char*)&buffer.sizeOfData, sizeof(buffer.sizeOfData), 0);
    while (bytesReceived < sizeof(buffer.sizeOfData)) {
        int currentBytes = recv(socket, reinterpret_cast<char*>(&buffer.sizeOfData) + bytesReceived, sizeof(buffer.sizeOfData) - bytesReceived, 0);

        if (currentBytes <= 0) {
            int error = errno;
            std::cout << "error in getting size of data num " << error << std::endl;
            return Buffer{ .status = 1 };
        }

        bytesReceived += currentBytes;
    }

    // Allocate memory for data buffer
   

    if(buffer.sizeOfData>0)
    {
        buffer.data = new char[buffer.sizeOfData + 1];
        bytesReceived = recv(socket, buffer.data, buffer.sizeOfData, 0);
        if (bytesReceived < buffer.sizeOfData)
        {
            buffer.sizeOfData = bytesReceived;
            char* temp = new char[buffer.sizeOfData + 1];

            std::memcpy(temp, buffer.data, buffer.sizeOfData);
            delete[] buffer.data;

            buffer.data = new char[buffer.sizeOfData + 1];
            std::memcpy(buffer.data, temp, buffer.sizeOfData);
            delete[] temp;


        }
        else if (bytesReceived > buffer.sizeOfData)
        {
            return Buffer{ .status = 1 }; //we have no status named 1 witch means the next handler to take it will fail and throw an error
        }
        buffer.data[buffer.sizeOfData] = '\0';
        // Set time stamp for buffer
    }
    buffer.time = std::chrono::high_resolution_clock::now();
    
    return buffer;
}

