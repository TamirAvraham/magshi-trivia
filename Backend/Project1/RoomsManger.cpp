#include "RoomsManger.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()
RoomData Room::DatafromJson(const http::json::JsonObject& json)
{
	return RoomData{
		.id = getIntFromJson(id),
		.name = json["name"].string_value(),
		.maxPlayers = getIntFromJson(maxPlayers),
		.numOfQustions = getIntFromJson(numOfQustions),
		.TimePerQuestion = getIntFromJson(TimePerQuestion),
		.isActive = false
	};
}

Room Room::fromJson(const http::json::JsonObject& json)
{
	Room ret;
	
	ret.data = DatafromJson(json);
	
	return ret;
}

std::vector<std::string> Room::getAllUsers()
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
