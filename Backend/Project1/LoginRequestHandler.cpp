#include "LoginRequestHandler.h"
#include "JsonObject.h"
#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
bool LoginRequestHandler::IsValid(unsigned char status)
{
    return status==LOGIN;
}

Responce* LoginRequestHandler::HandlerRequest(Request* req)
{
    auto ret= LoginResponce();
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	ret.next = nullptr;
	try
	{
		LoginRequest* loginRequest = (LoginRequest*)req;
		retBuffer.status = OK;
		auto instence = RequsetFactory::getInstence();
		instence.getLoginManager().Login(loginRequest->_username, loginRequest->_password);
		
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
	
    return &ret;
}

Request* LoginRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new LoginRequest(JsonRequestPacketDeserializer::deserializeLoginRequest(buffer));
}
