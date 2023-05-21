#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
bool SignupRequestHandler::IsValid(unsigned char status)
{
    return status == SIGNUP;
}

Responce* SignupRequestHandler::HandlerRequest(Request* req)
{
    auto ret = SignUpResponce();
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	ret.next = nullptr;
	try
	{
		SignUpRequest* signupRequest = (SignUpRequest*)req;
		retBuffer.status = OK;
		auto instence = RequsetFactory::getInstence();
		instence.getLoginManager().Signup(signupRequest->_username, signupRequest->_password, signupRequest->_email);
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
	return &ret;
}

Request* SignupRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new SignUpRequest(JsonRequestPacketDeserializer::deserializeSignUpRequest(buffer));
}
