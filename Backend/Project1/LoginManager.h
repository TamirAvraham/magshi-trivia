#pragma once
#include <vector>
#include "loggedUser.h"
class IDatabase;
class LoginManager
{
private:
	std::vector<LoggedUser> _loggedUsers;
public:
	void Signup(const std::string& username, const std::string& password, const std::string& email);
	void Login(const std::string& username, const std::string& password);
	void Logout(const std::string& username);

};

