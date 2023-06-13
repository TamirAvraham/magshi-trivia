#pragma once
#include "IRequestHandler.h"
#define ARHM(name) inline name##Responce handle##name##Request(const Request* req);
class AdminRoomHandler: public IRequestHandler
{
public:
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;

private:
	inline StartGameResponce handleStartGameRequest(const Request* req);
	inline LeaveRoomResponce handleLeaveRoomRequest(const Request* req);
	inline CloseRoomResponce handleCloseRoomRequest(const Request* req);
	inline GetRoomStateResponce handleGetRoomStateRequest(const Request* req);
};

