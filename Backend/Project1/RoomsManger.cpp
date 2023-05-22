#include "RoomsManger.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()
//RoomData Room::DatafromJson(const http::json::JsonObject& json)
//{
//	return RoomData{
//		.id = getIntFromJson(id),
//		.name = json["name"].string_value(),
//		.maxPlayers = getIntFromJson(maxPlayers),
//		.numOfQustions = getIntFromJson(numOfQustions),
//		.TimePerQuestion = getIntFromJson(TimePerQuestion),
//		.isActive = false
//	};
//}



RoomData Room::getData() const
{
	return data;
}

std::vector<std::string> Room::getAllUsers() const
{
	std::vector <std::string> ret;
	for (const auto& user : users)
		ret.push_back(user.username);
	return ret;
}

void Room::AddUser(const LoggedUser& user)
{
	users.push_back(user);
}

void Room::removeUser(const LoggedUser& user)
{
	std::remove_if(users.begin(), users.end(), [user](const LoggedUser& u)->bool { return user.username == u.username; });
}

bool RoomManger::getRoomStatus(int id) const
{
	auto room = rooms.find(id);
	if (rooms.end()==room)
	{
		throw std::exception("room did not exist");
	}
	return room->second.getData().isActive;
}

void RoomManger::createRoom(const LoggedUser& user, const RoomData& roomData)
{
	
	rooms.insert({ roomData.id,Room(roomData, user) });
}



void RoomManger::removeRoom(int id)
{
	rooms.erase(id);
}

Room& RoomManger::getRoom(int id)
{
	auto room = rooms.find(id);
	if (rooms.end() == room)
	{
		throw std::exception("room did not exist");
	}
	return room->second;
}

std::vector<RoomData> RoomManger::getRooms()
{
	std::vector<RoomData> ret;
	for (const auto& room : rooms)
		ret.push_back(room.second.getData());
	return ret;
}


Room::Room(const RoomData& data, const LoggedUser& user): data(data)
{
	users.push_back(user);
}
