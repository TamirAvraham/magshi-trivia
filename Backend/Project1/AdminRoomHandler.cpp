#include "AdminRoomHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
#include "MenuHandler.h"
#define retrunHandler(name) return new name##Responce(handle##name##Request(req));
bool AdminRoomHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == ADMIN_CHAR || RoomMemberHandler::IsValid(status);
	}
	catch (...)
	{
		return false;
	}
}

Responce* AdminRoomHandler::HandlerRequest(Request* req)
{
	if (RoomMemberHandler::IsValid(req->id))
	{
		auto ret =  RoomMemberHandler::HandlerRequest(req);
		if (ret)
		{
			delete ret->next;
			ret->next =new  AdminRoomHandler();
		}
		return ret;
	}
	switch (req->id)
	{
	case StartRoomCode:
		return new StartRoomResponce(handleStartRoomRequest(req));
	case CloseRoomCode:
		return new CloseRoomResponce(handleCloseRoomRequest(req));
	default:
		return nullptr;
	}
}

Request* AdminRoomHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	if (RoomMemberHandler::IsValid(buffer.status))
	{
		return RoomMemberHandler::GetRequestFromBuffer(buffer);
	}
	switch (buffer.status)
	{
	case StartRoomCode:
		return new StartRoomRequest(JsonRequestPacketDeserializer::deserializeStartRoomRequest(buffer));
	case CloseRoomCode:
		return new CloseRoomRequest(JsonRequestPacketDeserializer::deserializeCloseRoomRequest(buffer));
	default:
		return nullptr;
	}
}

inline StartRoomResponce AdminRoomHandler::handleStartRoomRequest(const Request* req)
{
	StartRoomResponce ret;
	auto request = static_cast<const StartRoomRequest*>(req);
	auto& roomManger = RequsetFactory::getInstence().getRoomsManager();

	if (!roomManger.isAdmin(request->roomId, request->username))
		throw std::invalid_argument("user is not room admin");

	roomManger.getRoom(request->roomId).start();
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = nullptr
	};
	ret.next = new MenuHandler();
	return ret;
}

inline CloseRoomResponce AdminRoomHandler::handleCloseRoomRequest(const Request* req)
{
	CloseRoomResponce ret;
	auto request = static_cast<const CloseRoomRequest*>(req);
	auto& roomManger = RequsetFactory::getInstence().getRoomsManager();

	if (!roomManger.isAdmin(request->roomId,request->username))
		throw std::invalid_argument("user is not room admin");

	roomManger.removeRoom(request->roomId);
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = nullptr
	};
	ret.next = new MenuHandler();
	return ret;
}
