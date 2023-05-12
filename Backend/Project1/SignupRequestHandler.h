#pragma once
#include "IRequestHandler.h"
#include "JsonObject.h"

class SignupRequestHandler :    public IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
};

