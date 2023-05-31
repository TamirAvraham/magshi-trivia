#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"]
#include "MenuHandler.h"
bool SignupRequestHandler::IsValid(unsigned char status)
{
    return status == SIGNUP;
}

Responce* SignupRequestHandler::HandlerRequest(Request* req)
{
    auto ret = SignUpResponce();
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	ret.next = new MenuHandler();
	bool noError = true;
	std::string retData;
	try
	{
		SignUpRequest* signupRequest = (SignUpRequest*)req;
		retBuffer.status = OK;
		auto instence = RequsetFactory::getInstence();
		instence.getLoginManager().Signup(signupRequest->_username, signupRequest->_password, signupRequest->_email);
	}
	catch (int errNum)
	{
		if (USER_EXISTS_ERROR == errNum)
		{
			std::cout << "User exists inside\n";
			retData = R"(
{
	"error": "signup failed, user already exists")";
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
	"error": "signup failed due to unexpected error")";
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

Request* SignupRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new SignUpRequest(JsonRequestPacketDeserializer::deserializeSignUpRequest(buffer));
}
