#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <list>

#define DB_FILE_NAME "GameDataBase.sqlite"

class SqliteDataBase :  public IDatabase
{
public:
	SqliteDataBase();
	bool open();
	virtual bool doesUserExist(std::string username) override;
	virtual bool doesPasswordMatch(std::string username, std::string password) override;
	virtual void addNewUser(std::string username, std::string password, std::string email) override;
private:
	bool sendSQL(const char* sqlCommand, int (*callback)(void*, int, char**, char**), void* data);
	sqlite3* _database;
};

struct User
{
	std::string username;
	std::string password;
	std::string email;
};

int callbackUser(void* data, int argc, char** argv, char** azColName);