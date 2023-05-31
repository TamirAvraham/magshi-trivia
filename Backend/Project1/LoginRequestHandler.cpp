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
	ret.next = new MenuHandler();
	bool noError = true;
	std::string retData;
	try
	{
		LoginRequest* loginRequest = (LoginRequest*)req;
		retBuffer.status = OK;
		auto instence = RequsetFactory::getInstence();
		instence.getLoginManager().Login(loginRequest->_username, loginRequest->_password);
		
	}
	catch (int errNum)
	{
		if (WRONG_PASSWORD_ERROR == errNum)
		{
			std::cout << "Wrong password inside\n";
			retData = R"""(
{
	"error": "login failed, incorrect password")""";
			retBuffer.status = Error;
			noError = false;
		}
		else
			throw std::exception();
	}
	catch (...)
	{
		retData = R"(
{
	"error": "login failed due to an unexpected error")";
		retBuffer.status = Error;
		noError = false;
	}
	if (noError)
	{
		retData = retJsonMessage.ToString();
	}
	retBuffer.sizeOfData = retData.length();
	retBuffer.data = const_cast<char*>(retData.c_str());
	ret.buffer = retBuffer;
	
    return &ret;
}

Request* LoginRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new LoginRequest(JsonRequestPacketDeserializer::deserializeLoginRequest(buffer));
}
