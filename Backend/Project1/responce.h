#pragma once
#include "requests.h"

#define ResponceStruct(responce_name) struct responce_name :Responce{ responce_name()=default; }
class IRequestHandler;
struct Responce
{
	Buffer buffer;
	IRequestHandler* next;

	Responce(const Buffer& buffer, IRequestHandler* next)
		: buffer(buffer), next(next)
	{
	}
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
struct GetHighScoreResponce :Responce {
	GetHighScoreResponce() = default;
};
ResponceStruct(CreateRoomResponce);
ResponceStruct(GetPersonalStatsResponce);
ResponceStruct(JoinRoomResponce);