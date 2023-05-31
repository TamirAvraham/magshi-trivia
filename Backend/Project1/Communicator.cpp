#include "Communicator.h"
#include "LoginRequestHandler.h"
#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
#include <future>


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
            while (handler!=nullptr)
            {
                //procees request
                Responce* responce;
                try
                {
                   auto request = handler->GetRequestFromBuffer(buffer);
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
                    handler = responce->next;
                    
                    //free memory
                    //delete request;

                    responceBuffer = responce->buffer;
                    std::pair<char*, int>& byteArray = getByteArrayFromBuffer(responceBuffer);
                    send(newSocket, byteArray.first, byteArray.second, 0);
                }
                catch (const std::exception& e)
                {
                    http::json::JsonObject errorjson;
                    errorjson.insert({ "error",{e.what()} });
                    responceBuffer.status = Error;
                    responceBuffer.sizeOfData = errorjson.ToString().length();
                    responceBuffer.data = (char*)(errorjson.ToString().c_str());
                    std::pair<char*, int>& byteArray = getByteArrayFromBuffer(responceBuffer);
                    send(newSocket, byteArray.first, byteArray.second, 0);
                }

                buffer = getBuffer(newSocket);
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

    
    std::memcpy(formattedData + sizeOfStatusInHeader + sizeOfDataLengthInHeader, buffer.data, buffer.sizeOfData);

    
    std::pair<char*, int> result(formattedData, size);

    
    return result;
}

     

Buffer Communicator::getBuffer(SOCKET socket) const
{
    // Define buffer struct
    Buffer buffer;

    // Read status byte from socket
    int bytesReceived = recv(socket, (char*)&buffer.status, sizeof(buffer.status), 0);
    if (bytesReceived != sizeof(buffer.status))
    {
        // Handle error
        // ...
    }

    // Read size of data (4 bytes) from socket
    bytesReceived = recv(socket, (char*)&buffer.sizeOfData, sizeof(buffer.sizeOfData), 0);
    if (bytesReceived != sizeof(buffer.sizeOfData))
    {
        // Handle error
        // ...
    }

    // Allocate memory for data buffer
    buffer.data = new char[buffer.sizeOfData+1];

    // Read data from socket
    bytesReceived = recv(socket, buffer.data, buffer.sizeOfData, 0);
    if (bytesReceived != buffer.sizeOfData)
    {
        // Handle error
        // ...
    }
    buffer.data[buffer.sizeOfData] = '\0';
    // Set time stamp for buffer
    buffer.time = std::chrono::high_resolution_clock::now();
    
    return buffer;
}

