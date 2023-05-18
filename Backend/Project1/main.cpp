#include <iostream>
#include "Communicator.h"
#include "SqliteDataBase.h"

int main() {
	Communicator com(12, "127.0.0.1");
	com.startHandlingRequest();
	std::string input;
	do
	{
		std::cin >> input;
		if (input == "TEST" || input == "test")
		{
			system(R"(python3 ../Tester/Tester.py)");
		}
	} while (input!="EXIT");
	exit(0);
}