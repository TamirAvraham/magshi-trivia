#pragma once
#include "requests.h"

#define ResponceStruct(responce_name) struct responce_name##Responce :Responce{ }
class IRequestHandler;
struct Responce
{
	Buffer buffer;
	IRequestHandler* next;

	
};
struct LoginResponce :Responce
{
	LoginResponce() = default;
};
struct SignUpResponce : Responce
{
	SignUpResponce() = default;
};
struct LogoutResponce:Responce
{
	LogoutResponce() = default;
};

//rooms related
struct GetRoomsResponce:Responce{};
struct GetRoomPlayersResponce :Responce { };
struct CreateRoomResponce :Responce { };
struct JoinRoomResponce :Responce { };
struct RemoveRoomResponce :Responce { };
struct GetRoomStatusResponce :Responce { };

//statistics related
struct GetTopPlayersResponce :Responce { };
struct GetPlayerStatisticsResponce :Responce { };