#include <iostream>
#include "Communicator.h"
constexpr int port = 100;
constexpr char ip[] = "127.0.0.1";

int main() {
	Communicator com(port, ip);
	com.startHandlingRequest();
	std::string input;
	do
	{
		std::cin >> input;
	} while (input!="EXIT");
	exit(0);
}