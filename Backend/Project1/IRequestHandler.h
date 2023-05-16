#pragma once
#include "requests.h"
#include "responce.h"
class IRequestHandler
{
public:
	virtual bool IsValid(unsigned char status)=0;
	virtual Responce* HandlerRequest(Request* req)=0;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer)=0;
};

