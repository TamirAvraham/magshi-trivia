#include <iostream>
#include "Communicator.h"
constexpr int port = 12;
constexpr char ip[] = "127.0.0.1";

int main() {
	Communicator com(port, ip);
	com.startHandlingRequest();
	std::string input;
	do
	{
		std::cin >> input;
		if (input=="TEST"||input=="test")
		{
			system(R"(python3 ../Tester/Tester.py)");
		}
	} while (input!="EXIT");
	exit(0);
}