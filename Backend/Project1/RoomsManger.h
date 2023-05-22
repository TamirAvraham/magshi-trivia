#pragma once
#include "loggedUser.h"
#include "JsonObject.h"
#include <vector>
struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQustions;
	unsigned int TimePerQuestion;
	bool isActive;
};
class Room {
private:
	RoomData data;
	std::vector<LoggedUser> users;
	static RoomData DatafromJson(const http::json::JsonObject& json);
public:
	static Room fromJson(const http::json::JsonObject& json);
	std::vector<std::string> getAllUsers();
	void AddUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
};