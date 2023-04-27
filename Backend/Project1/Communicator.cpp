#include "Communicator.h"
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
        if (newSocket < 0)
        {

            PWSTR str = nullptr;
            InetNtop(_socketAddress.sin_family, &_socketAddress.sin_addr.s_addr, str, 50);
            exit(888);
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
