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

class RoomManger {
private:
	std::map<int, Room> rooms;
public:
	bool getRoomStatus(int id)const;
	void createRoom(const LoggedUser& user, const RoomData& roomData);
	void removeRoom(int id);
	Room& getRoom(int id);
	std::vector<RoomData> getRooms();
};