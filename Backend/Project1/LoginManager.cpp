#include "LoginManager.h"

void LoginManager::Signup(const std::string& username, const std::string& password, const std::string& email)
{
	auto& db = SqliteDataBase::GetInstance();
	if (!db.doesUserExist(username))
	{
		db.addNewUser(username, password, email);
		_loggedUsers.emplace_back(username);
	}
	else
	{
		throw USER_EXISTS_ERROR;
	}
}

void LoginManager::Login(const std::string& username, const std::string& password)
{
	if (SqliteDataBase::GetInstance().doesPasswordMatch(username, password))
	{
		_loggedUsers.emplace_back(username);
	}
	else
	{
		throw WRONG_PASSWORD_ERROR;
	}
	
}

void LoginManager::Logout(const std::string& username)
{
	auto userIter = std::find_if(_loggedUsers.begin(), _loggedUsers.end(), [&username](const LoggedUser& user) { return user.username == username; });
	if (userIter != _loggedUsers.end())
	{
		_loggedUsers.erase(userIter);
	}
}

LoggedUser& LoginManager::getUser(const std::string& username)
{
	auto user = std::find_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) { return user.username == username; });
	if (user==_loggedUsers.end())
	{
		throw std::exception("user was not logged in");
	}
	return *user;
}

LoginManager::LoginManager()
{
}
