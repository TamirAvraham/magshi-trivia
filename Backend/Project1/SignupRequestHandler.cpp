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
		SignUpRequest* signupRequest = (SignUpRequest*)req;		// the req has id 0 before this line (no content)
		retBuffer.status = OK;
		//RequsetFactory::getInstence().getLoginManager().Signup(signupRequest->_username, signupRequest->_password, signupRequest->_email);

		//For now I temporarily created values, once the issue will be fixed the values would be actual ones
		// I believe there is the same issue with login option, please check it
		RequsetFactory::getInstence().getLoginManager().Signup("Tamir", "Fix", "Me");
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
