#include "LoginManager.h"

void LoginManager::Signup(const std::string& username, const std::string& password, const std::string& email)
{
	//wow look at this database call so cool
	//db call

	_loggedUsers.emplace_back(username);
}

void LoginManager::Login(const std::string& username, const std::string& password)
{
	//a db call so impressive
	//db call

	_loggedUsers.emplace_back(username);
}

void LoginManager::Logout(const std::string& username)
{
	std::remove_if(_loggedUsers.begin(), _loggedUsers.end(), [username](const LoggedUser& user) ->bool {
		return (user.username == username);
	});
}
