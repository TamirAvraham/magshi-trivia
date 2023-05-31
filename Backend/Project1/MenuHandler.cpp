
#include "MenuHandler.h"
#include "RoomsHandlers.h"
#include "StatisticsHandler.h"
bool MenuHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == STATISTICS_CHAR || secondDigit == ROOM_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* MenuHandler::HandlerRequest(Request* req)
{
	char secondDigit = std::to_string(((int)req->id))[0];
	MenuHandler menuHandler;
	StatisticsHandler statHandler;
	switch (secondDigit)
	{
	case ROOM_CHAR:
			return menuHandler.HandlerRequest(req);
	case STATISTICS_CHAR:
			return statHandler.HandlerRequest(req);
	default:
			return nullptr;
	}
}

Request* MenuHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	char secondDigit = std::to_string(((int)buffer.status))[0];
	MenuHandler menuHandler;
	StatisticsHandler statHandler;
	switch (secondDigit)
	{
	case ROOM_CHAR:
		return menuHandler.GetRequestFromBuffer(buffer);
	case STATISTICS_CHAR:
		return menuHandler.GetRequestFromBuffer(buffer);
	default:
		return nullptr;
	}
}
