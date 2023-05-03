#include "Communicator.h"
#include <future>
Communicator::Communicator(int port, std::string ip) :_ipAddress(ip), _port(port), _socketAddress_len(sizeof(_socketAddress)), _socketAddress()
{
    if (startServer() != 1)
    {
        std::wcout << "Failed to start server with PORT: " << ntohs(_socketAddress.sin_port);
        
    }
    else
    {
        startListen();
    }
}
inline int Communicator::startServer()
{
    PVOID pAddrBuf;
    if (WSAStartup(MAKEWORD(2, 0), &_wsaData) != 0)
    {
        std::cerr << "error in wsa start up";
        exit(INTERNAL_WINSOCK_ERROR);
    }

    _ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_ListenSocket == INVALID_SOCKET)
    {
        std::cerr << "error in listen ";
        std::cerr << "error code is:" << WSAGetLastError();
        exit(INTERNAL_WINSOCK_ERROR);
    }
    
    _socketAddress.sin_family = AF_INET;
    _socketAddress.sin_port = htons(_port);

    std::wstring widestr = std::wstring(_ipAddress.begin(), _ipAddress.end());
    const wchar_t* widecstr = widestr.c_str();

    InetPton(_socketAddress.sin_family, widecstr, &_socketAddress.sin_addr.s_addr);

    if (bind(_ListenSocket, (sockaddr*)&_socketAddress, _socketAddress_len) != 0)
    {
        std::cerr << "error in bind";
        exit(INTERNAL_WINSOCK_ERROR);
    }

    return 1;
}

inline void Communicator::startListen()
{
    if (listen(_ListenSocket,20)!=0)
    {
        std::cerr << WSAGetLastError();
        exit(LISTEN_ERROR);
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
        if (newSocket < 0)
        {

            PWSTR str = nullptr;
            InetNtop(_socketAddress.sin_family, &_socketAddress.sin_addr.s_addr, str, 50);
            exit(NEW_SOCKET_CANT_BE_ACCEPTED);
        }
        /*TODO:
        * switch this with request factory
        */
        IRequestHandler* handler = nullptr;
        _clients.emplace(newSocket, handler);

        /*TODO:
        * delete after 1.0.1
        */
        std::async(&send, newSocket, "hello world", sizeof("hello world"), 0);
    }
}
