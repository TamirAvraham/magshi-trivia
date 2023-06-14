#pragma once
#include "IRequestHandler.h"
class RoomMemberHandler:public IRequestHandler
{
public:
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;
private:
	inline LeaveRoomResponce handleLeaveRoomRequest(const LeaveRoomRequest request) const;
	inline GetRoomStateResponce handleGetRoomStateRequest(const GetRoomStateRequest request) const;
};

