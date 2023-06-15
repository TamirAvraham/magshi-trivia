#pragma once
#include "IRequestHandler.h"
#include "RoomMemberHandler.h"
#define ARHM(name) inline name##Responce handle##name##Request(const Request* req);
class AdminRoomHandler: public RoomMemberHandler
{
public:
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;

private:
	inline StartRoomResponce handleStartRoomRequest(const Request* req);
	inline CloseRoomResponce handleCloseRoomRequest(const Request* req);
};

