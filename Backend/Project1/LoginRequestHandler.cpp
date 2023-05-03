#include "LoginRequestHandler.h"
#include "JsonObject.h"
bool LoginRequestHandler::IsValid(unsigned char status)
{
    return status==LOGIN;
}

Responce* LoginRequestHandler::HandlerRequest(Request* req)
{
    LoginResponce ret;
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	try
	{
		LoginRequest* loginRequest = (LoginRequest*)req;
		retBuffer.status = OK;
		
	}
	catch (...)
	{
		retJsonMessage = R"(
{
	"error": "login failed")";
		retBuffer.status = Error;
	}
	std::string retData = retJsonMessage.ToString();
	retBuffer.sizeOfData = retData.length();
	retBuffer.data = const_cast<char*>(retData.c_str());
	ret.buffer = retBuffer;
	ret.next = nullptr; 
    return &ret;
}
