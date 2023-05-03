#pragma once
#include "requests.h"
class JsonRequestPacketDeserializer
{
	
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignUpRequest deserializeSignUpRequest(Buffer buffer);
};

