#include "RoomsHandlers.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonSirealizer.h"
#include "RequsetFactory.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()

bool RoomsHandler::IsValid(unsigned char status)
{
	char secondDigit = std::to_string(((int)status))[0];
    return secondDigit==ROOM_CHAR;
}

Responce* RoomsHandler::HandlerRequest(Request* req)
{
	switch (req->id)
	{
	case getRoomCode:

	default:
		break;
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
	default:
		return nullptr;
		
	}
}

inline GetRoomPlayersResponce RoomsHandler::handleGetRoomPlayersRequest(const GetRoomPlayersRequest requset) const
{
	GetRoomPlayersResponce ret;
	auto players = RequsetFactory::getInstence().getRoomsManager().getRoom(requset.roomId).getAllUsers();
	auto data = http::json::JsonObject();
	data.insert({ "players",{JsonSirealizer::getVectorAsString(players)} });
	auto buffer = Buffer{ 
		.status = OK,
		.sizeOfData = (unsigned int)data.ToString().size(),
		.data = const_cast<char*>(data.ToString().c_str())
	};
	ret.buffer = buffer;
	ret.next = new RoomsHandler();
	return ret;
}

inline GetRoomsResponce RoomsHandler::handleGetRoomsRequest(const GetRoomsRequest request) const
{
	GetRoomsResponce ret;
	auto rooms = RequsetFactory::getInstence().getRoomsManager().getRooms();
	auto data = http::json::JsonObject();
	data.insert({ "rooms",{JsonSirealizer::getVectorAsString(rooms)} });
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = (unsigned int)data.ToString().size(),
		.data = const_cast<char*>(data.ToString().c_str())
	};
	ret.buffer = buffer;
	ret.next = new RoomsHandler();
}

inline CreateRoomResponce RoomsHandler::handleCreateRoomRequest(const CreateRoomRequest request) const
{

	CreateRoomResponce ret;
	auto& factory=RequsetFactory::getInstence(); 
	factory.getRoomsManager().createRoom(factory.getLoginManager().getUser(request.username),request.roomData);
	ret.next = new RoomsHandler();
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = const_cast<char*>("")
	};
	return ret;
}

inline RemoveRoomResponce RoomsHandler::handleRemoveRoomRequest(const RemoveRoomRequest request) const
{
	RemoveRoomResponce ret;
	RequsetFactory::getInstence().getRoomsManager().removeRoom(request.roomId);
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = const_cast<char*>("")
	};
	ret.next = new RoomsHandler();

	return ret;
}

inline GetRoomStatusResponce RoomsHandler::handleGetRoomStatusRequest(const GetRoomStatusRequest request) const
{
	RemoveRoomResponce ret;
	auto status=RequsetFactory::getInstence().getRoomsManager().getRoomStatus(request.roomId);
	auto data = http::json::JsonObject();
	data.insert({ "status",{status ? "true" : "false"} });
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = (unsigned int)data.ToString().size(),
		.data = const_cast<char*>(data.ToString().c_str())
	};
	ret.buffer = buffer;
	ret.next = new RoomsHandler();
}
