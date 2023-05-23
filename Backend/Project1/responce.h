#pragma once
#include "requests.h"

#define ResponceStruct(responce_name) struct responce_name :Responce{ }
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
struct GetRoomsResponce:Responce
{
	GetRoomsResponce() = default;
};
struct GetRoomResponce :Responce { };
struct GetHighScoreResponce :Responce {
	GetHighScoreResponce() = default;
};
struct CreateRoomResponce :Responce { };
struct GetPersonalStatsResponce :Responce { };
struct JoinRoomResponce :Responce { };
struct RemoveRoomResponce :Responce { };
