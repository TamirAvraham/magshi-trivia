#include "RoomsHandlers.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonSirealizer.h"
#include "RequsetFactory.h"
#include "RoomMemberHandler.h"
#include "AdminRoomHandler.h"
#include "LoginRequestHandler.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()
#define retrunHandler(name) return new name##Responce(handle##name##Request((name##Request)(*req)));

bool RoomsHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == ROOM_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* RoomsHandler::HandlerRequest(Request* req)
{
	switch (req->id)
	{
	case getRoomCode:
		return new GetRoomPlayersResponce(handleGetRoomPlayersRequest((GetRoomPlayersRequest*)(req)));
	case deleteRoomCode:
		return new RemoveRoomResponce(handleRemoveRoomRequest((RemoveRoomRequest*)(req)));
	case getRoomsCode:
		return new GetRoomsResponce(handleGetRoomsRequest((GetRoomsRequest*)(req)));
	case createRoomCode:
		return new CreateRoomResponce(handleCreateRoomRequest((CreateRoomRequest*)(req)));
	case getRoomStatus:
		return new GetRoomStatusResponce(handleGetRoomStatusRequest((GetRoomStatusRequest*)(req)));
	case joinRoomCode:
		return new JoinRoomResponce(handleJoinRoomRequest((JoinRoomRequest*)(req)));
	case logoutCode:
		return new LogoutResponce(handleLogoutRequest((LogoutRequest*)(req)));
	default:
		return nullptr;
	}
	return nullptr;
}

Request* RoomsHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case getRoomCode:
		return new GetRoomPlayersRequest(JsonRequestPacketDeserializer::deserializeGetRoomRequest(buffer));
	case deleteRoomCode:
		return new RemoveRoomRequest(JsonRequestPacketDeserializer::deserializeRemoveRoomRequest(buffer));
	
	case getRoomsCode:
		return new GetRoomsRequest(JsonRequestPacketDeserializer::deserializeRoomsRequest(buffer));
	case createRoomCode:
		return new CreateRoomRequest(JsonRequestPacketDeserializer::deserializeCreateRoomsRequset(buffer));
	case getRoomStatus:
		return new GetRoomStatusRequest(JsonRequestPacketDeserializer::deserializeGetRoomStatusRequest(buffer));
	case joinRoomCode:
		return new JoinRoomRequest(JsonRequestPacketDeserializer::deserializeJoinRoomRequest(buffer));
	case logoutCode:
		return new LogoutRequest(JsonRequestPacketDeserializer::deserializeLogoutRequest(buffer));
	default:
		return nullptr;
	}
}

inline LogoutResponce RoomsHandler::handleLogoutRequest(const LogoutRequest* request) const
{
	RequsetFactory::getInstence().getLoginManager().Logout(request->username);
	LogoutResponce ret;
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = nullptr
	};
	ret.next = new LoginRequestHandler();
	return ret;
}

inline GetRoomPlayersResponce RoomsHandler::handleGetRoomPlayersRequest(GetRoomPlayersRequest* requset) const
{
	GetRoomPlayersResponce ret;
	auto players = RequsetFactory::getInstence().getRoomsManager().getRoom(requset->roomId).getAllUsers();
	auto data = http::json::JsonObject();
	data.insert({ "players",{JsonSirealizer::getVectorAsString(players)} });
	std::string dataAsString = data.ToString();
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};
	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';
	ret.buffer = buffer;
	ret.next = new MenuHandler();
	return ret;
}

inline GetRoomsResponce RoomsHandler::handleGetRoomsRequest(GetRoomsRequest* request) const
{
	GetRoomsResponce ret;
	auto rooms = RequsetFactory::getInstence().getRoomsManager().getRooms();
	auto data = http::json::JsonObject();
	data.insert({ "rooms", { JsonSirealizer::getVectorAsString(rooms) } });
	std::string dataAsString = data.ToString();  
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]  
	};
	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';  
	ret.buffer = buffer;
	ret.next = new MenuHandler();
	return ret;
}

inline CreateRoomResponce RoomsHandler::handleCreateRoomRequest(CreateRoomRequest* request) const
{

	CreateRoomResponce ret;
	auto& factory=RequsetFactory::getInstence(); 
	auto& LoginManager = factory.getLoginManager();

	int roomId=factory.getRoomsManager().createRoom(LoginManager.getUser(request->username),request->roomData);

	auto data = http::json::JsonObject();
	data.insert({ "id", { std::to_string(roomId)}});
	std::string dataAsString = data.ToString();

	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = new AdminRoomHandler();

	return ret;
}

inline RemoveRoomResponce RoomsHandler::handleRemoveRoomRequest(RemoveRoomRequest* request) const
{
	RemoveRoomResponce ret;
	RequsetFactory::getInstence().getRoomsManager().removeRoom(request->roomId);
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = nullptr
	};
	ret.next = new MenuHandler();

	return ret;
}

inline GetRoomStatusResponce RoomsHandler::handleGetRoomStatusRequest(GetRoomStatusRequest* request) const
{
	GetRoomStatusResponce ret;
	auto status=RequsetFactory::getInstence().getRoomsManager().getRoomStatus(request->roomId);
	auto data = http::json::JsonObject();
	data.insert({ "status",{status ? "true" : "false"} });
	std::string dataAsString = data.ToString();
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};
	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';
	ret.buffer = buffer;
	ret.next = new MenuHandler();
	return ret;
}

inline JoinRoomResponce RoomsHandler::handleJoinRoomRequest(JoinRoomRequest* request) const
{
	JoinRoomResponce ret;
	LoggedUser us;
	us.username = request->username;
	RequsetFactory::getInstence().getRoomsManager().joinRoom(request->roomId, us);
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = nullptr
	};
	ret.next = new RoomMemberHandler();
	return ret;
}


