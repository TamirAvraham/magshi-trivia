#pragma once
#include "IRequestHandler.h"
//2 is for room related request
//the second number is for the request
constexpr char ROOM_CHAR = '2';
constexpr unsigned char getRoomCode = 21;
constexpr unsigned char getRoomsCode = 22;
constexpr unsigned char deleteRoomCode = 23;
constexpr unsigned char createRoomCode = 24;
constexpr unsigned char getRoomStatus = 25;


class RoomsHandler : public IRequestHandler
{
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;
};

