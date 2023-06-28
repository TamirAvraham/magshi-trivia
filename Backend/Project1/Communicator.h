#pragma once
#include <WinSock2.h>
#include <iostream>

#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <functional>
#include <thread>
#include <map>

#include "IRequestHandler.h"
#include "requests.h"
#pragma comment(lib, "Ws2_32.lib")


constexpr unsigned short sizeOfHeader = 5;
constexpr unsigned short sizeOfDataLengthInHeader = sizeof(unsigned int);
constexpr unsigned short sizeOfStatusInHeader = 1;

class Communicator
{
public:
	Communicator(int port, std::string ip);
	//ctor helpers
private:
	inline int startServer();
	inline void startListen();

// members for server

	int _port;
	std::string _ipAddress;
	WSADATA _wsaData;
	SOCKET _ListenSocket;
	sockaddr_in _socketAddress;
	socklen_t _socketAddress_len;

public:
	void startHandlingRequest();
private:
	std::map<SOCKET, IRequestHandler*> _clients;
	
	void Handler();
	Buffer getBuffer(SOCKET)const;
	std::pair<char*,int>& getByteArrayFromBuffer(const Buffer& buffer)const;
	void mehtod(SOCKET);
};

