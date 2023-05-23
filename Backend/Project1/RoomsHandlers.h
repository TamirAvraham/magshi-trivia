#pragma once
#include "IRequestHandler.h"
#define RoomsHandlerMethod(param)  inline param##Responce handle##param##Request(const param##Request request) const



class RoomsHandler : public IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;
private:
	inline GetRoomPlayersResponce handleGetRoomPlayersRequest(const GetRoomPlayersRequest requset) const;
	inline GetRoomsResponce handleGetRoomsRequest(const GetRoomsRequest request) const;
	inline CreateRoomResponce handleCreateRoomRequest(const CreateRoomRequest request) const;
	inline RemoveRoomResponce handleRemoveRoomRequest(const RemoveRoomRequest request) const;
	inline GetRoomStatusResponce handleGetRoomStatusRequest(const GetRoomStatusRequest request) const;
};

