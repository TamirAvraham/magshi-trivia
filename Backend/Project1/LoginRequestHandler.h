#pragma once
#include "IRequestHandler.h"
#include "requests.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status);
	virtual Responce* HandlerRequest(Request* req);
};

