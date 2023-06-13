#include "AdminRoomHandler.h"

bool AdminRoomHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == ADMIN_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* AdminRoomHandler::HandlerRequest(Request* req)
{
    return nullptr;
}

Request* AdminRoomHandler::GetRequestFromBuffer(const Buffer& buffer)
{
    return nullptr;
}
