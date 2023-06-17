#include "RoomsManger.h"
#include "JsonSirealizer.h"
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

void RoomManger::createRoom(LoggedUser user, const RoomData& roomData)
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

void RoomManger::joinRoom(int id, const LoggedUser& user)
{
	auto room = rooms.find(id);
	if (room == rooms.end())
	{
		throw std::exception("room did not exist");
	}
	room->second.AddUser(user);
}

bool RoomManger::isAdmin(int id, const std::string& username) const
{
	try
	{
		auto user = LoggedUser{ .username = username };
		return rooms.at(id).isAdmin(user);
	}
	catch (...)
	{
		return false;
	}
}

void RoomManger::removeUser(int roomId, const LoggedUser& user)
{
	rooms.at(roomId).removeUser(user);
}

RoomManger::RoomManger()
{
	auto data= RoomData{
		.id = 900,
		.name = "test",
		.maxPlayers = 30,
		.numOfQustions = 10,
		.TimePerQuestion = 5,
		.isActive = false
	};
	createRoom({ "beni" }, data);
}


Room::Room(const RoomData& data, const LoggedUser& user): data(data),admin(user)
{
	users.push_back(user);
	
}

inline bool Room::isAdmin(const LoggedUser& user) const
{
	return user==admin;
}

std::string Room::toString() const
{
	http::json::JsonObject json;
	json.insert({ "status",{data.isActive ? "true" : "false"} });
	json.insert({ {"players"}, { JsonSirealizer::getVectorAsString(users)} });
	json.insert({ "answerCount",{"0"} });//change this when i figure out wtf this is
	json.insert({ {"answerTimeOut"},{"idfk"} });
	return json.ToString();
}

void Room::start()
{
	data.isActive = true;
	//add rest of start logic here
}
