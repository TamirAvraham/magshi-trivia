#pragma once
#include "loggedUser.h"
#include "JsonObject.h"
#include <vector>
#include <format>

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQustions;
	unsigned int TimePerQuestion;
	bool isActive;
	http::json::JsonObject toJson() {
		http::json::JsonObject object;
		object.insert({ "id",{std::to_string(id)} });
		object.insert({ "name",{name} });
		object.insert({ "maxPlayers",{std::to_string(maxPlayers)} });
		object.insert({ "numOfQustions",{ std::to_string(numOfQustions) } });
		object.insert({ "TimePerQuestion",{ std::to_string(TimePerQuestion) } });
		object.insert({ "isActive",{isActive ? "true" : "false"} });
		return object;
	}
};
class Room {
private:
	RoomData data;
	std::vector<LoggedUser> users;
	/*static RoomData DatafromJson(const http::json::JsonObject& json);*/
public:
	
	RoomData getData()const;
	std::vector<std::string> getAllUsers()const;
	void AddUser(const LoggedUser& user);
	void removeUser(const LoggedUser& user);
	Room(const RoomData& data, const LoggedUser& user);
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