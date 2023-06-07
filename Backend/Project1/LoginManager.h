#pragma once
#include <vector>
#include "loggedUser.h"
#include "SqliteDataBase.h"

constexpr auto USER_EXISTS_ERROR = 418;
constexpr auto WRONG_PASSWORD_ERROR = 419;
class IDatabase;
class LoginManager
{
private:
	std::vector<LoggedUser> _loggedUsers;
	/*SqliteDataBase& _db;*/
public:
	void Signup(const std::string& username, const std::string& password, const std::string& email);
	void Login(const std::string& username, const std::string& password);
	void Logout(const std::string& username);
	LoggedUser& getUser(const std::string& username);
	LoginManager();
};

