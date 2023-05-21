#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	if (!open())
	{
		std::cout << "Failed to open the database file!\n";
		exit(EXIT_FAILURE);
	}
}

// Open (or creates) the database file
bool SqliteDataBase::open()
{
	if (sqlite3_open(DB_FILE_NAME, &_database) != SQLITE_OK)
	{
		_database = nullptr;
		std::cout << "Failed to open DB\n";
		return false;
	}
	sendSQL("CREATE TABLE IF NOT EXISTS users ( username TEXT UNIQUE NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);", nullptr, nullptr);
	return true;
}
bool SqliteDataBase::doesUserExist(std::string username)
{
	std::list<User> users;
	sendSQL(("SELECT * FROM users WHERE username  = '" + username + "';").c_str(), callbackUser, &users);
	return users.size() > 0;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	std::list<User> users;
	sendSQL(("SELECT * FROM users WHERE username  = '" + username + "' AND password = '" + password + "';").c_str(), callbackUser, &users);
	return users.size() > 0;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sendSQL(("INSERT INTO users VALUES ('" + username + "', '" + password + "', '" + email + "');").c_str(), nullptr, nullptr);
}

bool SqliteDataBase::sendSQL(const char* sqlCommand, int (*callback)(void*, int, char**, char**), void* data)
{
	if (sqlite3_exec(_database, sqlCommand, callback, data, nullptr) != SQLITE_OK) //Send SQL command
	{
		std::cout << "Failure: " << sqlCommand << std::endl;
		return false;
	}
	return true;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 0)	// No argument
		return 0;
	std::string name(argv[0]);
	std::string password(argv[1]);
	std::string email(argv[2]);
	User newUser;
	newUser.username = name;
	newUser.password = password;
	newUser.email = email;
	((std::list<User>*)data)->push_back(newUser);	// Adding User to the list
	return 0;
}