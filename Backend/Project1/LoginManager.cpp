#include "LoginManager.h"

void LoginManager::Signup(const std::string& username, const std::string& password, const std::string& email)
{
	if (!_db.doesUserExist(username))
	{
		_db.addNewUser(username, password, email);
		_loggedUsers.emplace_back(username);
	}
}

void LoginManager::Login(const std::string& username, const std::string& password)
{
	if (_db.doesPasswordMatch(username, password))
	{
		_loggedUsers.emplace_back(username);
	}
}

void LoginManager::Logout(const std::string& username)
{
	std::remove_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) ->bool {
		return (user.username == username);
		});
}

LoggedUser& LoginManager::getUser(const std::string& username)
{
	auto user=std::find(_loggedUsers.begin(), _loggedUsers.end(),username);
	if (user==_loggedUsers.end())
	{
		throw std::exception("user was not logged in");
	}
	return *user;
}
