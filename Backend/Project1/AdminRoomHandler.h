#pragma once
#include "IRequestHandler.h"
class AdminRoomHandler: public IRequestHandler
{
public:
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;

private:
	
};

