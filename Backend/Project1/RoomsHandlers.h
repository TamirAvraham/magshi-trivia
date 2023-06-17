#pragma once
#include "IRequestHandler.h"
#include "MenuHandler.h"
#define RoomsHandlerMethod(param)  inline param##Responce handle##param##Request(const param##Request request) const



class RoomsHandler : public IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;
private:
	inline GetRoomPlayersResponce handleGetRoomPlayersRequest(GetRoomPlayersRequest* requset) const;
	inline GetRoomsResponce handleGetRoomsRequest(GetRoomsRequest* request) const;
	inline CreateRoomResponce handleCreateRoomRequest(CreateRoomRequest* request) const;
	inline RemoveRoomResponce handleRemoveRoomRequest(RemoveRoomRequest* request) const;
	inline GetRoomStatusResponce handleGetRoomStatusRequest(GetRoomStatusRequest* request) const;
	inline JoinRoomResponce handleJoinRoomRequest(JoinRoomRequest* request) const;
	
};

