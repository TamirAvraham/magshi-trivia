#include <iostream>
#include "Communicator.h"


int main() {
	Communicator com(12, "127.0.0.1");
	com.startHandlingRequest();
	std::string input;
	do
	{
		std::cin >> input;
	} while (input!="EXIT");
	exit(0);
}