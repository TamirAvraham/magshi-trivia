#pragma once
#include "IRequestHandler.h"
#include "requests.h"
#include "RequsetFactory.h"
#include "MenuHandler.h"

class LoginRequestHandler : public IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status)override;
	virtual Responce* HandlerRequest(Request* req)override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer)override;
};

