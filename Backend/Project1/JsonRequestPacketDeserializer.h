#pragma once
#include "requests.h"
#define JsonRequestPacketDeserializerMethod(struct_name) static struct_name deserialize ##struct_name (const Buffer& buffer)
class JsonRequestPacketDeserializer
{
	
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignUpRequest deserializeSignUpRequest(Buffer buffer);
	static GetRoomRequest deserializeGetRoomRequest(const Buffer& buffer);
	static RemoveRoomRequest deserializeRemoveRoomRequest(const Buffer& buffer);
	static RoomsRequest deserializeRoomsRequest(const Buffer& buffer);
	static CreateRoomsRequset deserializeCreateRoomsRequset(const Buffer& buffer);
	static GetRoomStatusRequest deserializeGetRoomStatusRequest(const Buffer& buffer);
private:
	static RoomData RoomDatafromJson(const http::json::JsonObject& json);
};

