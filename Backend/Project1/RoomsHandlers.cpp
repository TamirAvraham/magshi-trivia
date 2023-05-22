#include "RoomsHandlers.h"
#include "JsonRequestPacketDeserializer.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()

bool RoomsHandler::IsValid(unsigned char status)
{
	char secondDigit = std::to_string(((int)status))[0];
    return secondDigit==ROOM_CHAR;
}

Responce* RoomsHandler::HandlerRequest(Request* req)
{
    return nullptr;
}

Request* RoomsHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case getRoomCode:
		return new GetRoomRequest(JsonRequestPacketDeserializer::deserializeGetRoomRequest(buffer));
	case deleteRoomCode:
		return new RemoveRoomRequest(JsonRequestPacketDeserializer::deserializeRemoveRoomRequest(buffer));
	case getRoomsCode:
		return new RoomsRequest(JsonRequestPacketDeserializer::deserializeRoomsRequest(buffer));
	case createRoomCode:
		return new CreateRoomsRequset(JsonRequestPacketDeserializer::deserializeCreateRoomsRequset(buffer));
	case getRoomStatus:
		return new GetRoomStatusRequest(JsonRequestPacketDeserializer::deserializeGetRoomStatusRequest(buffer));
	default:
		return nullptr;
		
	}
}
