#include "AdminRoomHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
bool AdminRoomHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == ADMIN_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* AdminRoomHandler::HandlerRequest(Request* req)
{
    return nullptr;
}

Request* AdminRoomHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case StartRoomCode:
		return new StartRoomRequest(JsonRequestPacketDeserializer::deserializeStartRoomRequest(buffer));
	case getRoomStateCode:
		return new GetRoomStateRequest(JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(buffer));
	case CloseRoomCode:
		return new CloseRoomRequest(JsonRequestPacketDeserializer::deserializeCloseRoomRequest(buffer));
	case LeaveRoomCode:
		return new LeaveRoomRequest(JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(buffer));
	default:
		return nullptr;
	}
}

inline CloseRoomResponce AdminRoomHandler::handleCloseRoomRequest(const Request* req)
{
	CloseRoomResponce ret;
	auto request = static_cast<const CloseRoomRequest*>(req);
	auto& roomManger = RequsetFactory::getInstence().getRoomsManager();
	if (roomManger.isAdmin(request->roomId,request->username))
	{
		roomManger.removeRoom(request->roomId);
		
	}
}
