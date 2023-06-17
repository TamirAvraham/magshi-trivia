#include "RoomMemberHandler.h"
#include "RequsetFactory.h"
#include "JsonRequestPacketDeserializer.h"
bool RoomMemberHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == MEMBER_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* RoomMemberHandler::HandlerRequest(Request* req)
{
	switch (req->id)
	{
	case getRoomStateCode:
		return new GetRoomStateResponce(handleGetRoomStateRequest((GetRoomStateRequest*)(req)));
	case LeaveRoomCode:
		return new LeaveRoomResponce(handleLeaveRoomRequest((LeaveRoomRequest*)(req)));

	default:
		return nullptr;
	}
}

Request* RoomMemberHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case getRoomStateCode:
		return new GetRoomStateRequest(JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(buffer));
	case LeaveRoomCode:
		return new LeaveRoomRequest(JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(buffer));
	default:
		return nullptr;
	}
}
inline LeaveRoomResponce RoomMemberHandler::handleLeaveRoomRequest(LeaveRoomRequest* request) const
{
	LeaveRoomResponce ret;
	auto user = LoggedUser{ .username = request->username };
	RequsetFactory::getInstence().getRoomsManager().removeUser(request->roomId, user);
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = 0,
		.data = const_cast<char*>(""),
	};
	ret.buffer = buffer;
	ret.next = new RoomMemberHandler();
	return ret;
}

inline GetRoomStateResponce RoomMemberHandler::handleGetRoomStateRequest(GetRoomStateRequest* request) const
{
	GetRoomStateResponce ret;
	auto& roomData = RequsetFactory::getInstence().getRoomsManager().getRoom(request->roomId);
	auto data = roomData.toString();
	ret.buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(data.size()),
		.data = new char[data.size() + 1]

	};
	std::copy(data.begin(), data.end(), ret.buffer.data);
	ret.buffer.data[data.size()] = '\0';
	ret.next = new RoomMemberHandler();
	return ret;
}