#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
bool SignupRequestHandler::IsValid(unsigned char status)
{
    return status == SIGNUP;
}

Responce* SignupRequestHandler::HandlerRequest(Request* req)
{
    SignUpResponce ret;
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	try
	{
		SignUpRequest* signupRequest = (SignUpRequest*)req;
		retBuffer.status = OK;
		RequsetFactory::getInstence().getLoginManager().Signup(signupRequest->_username, signupRequest->_password, signupRequest->_email);
	}
	catch (...)
	{
		retJsonMessage = R"(
{
	"error": "signup failed")";
		retBuffer.status = Error;
	}
	std::string retData = retJsonMessage.ToString();
	retBuffer.sizeOfData = retData.length();
	retBuffer.data = const_cast<char*>(retData.c_str());
	ret.buffer = retBuffer;
	ret.next = nullptr;
	return &ret;
}

Request* SignupRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new Request(JsonRequestPacketDeserializer::deserializeSignUpRequest(buffer));
}
