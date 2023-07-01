#include "SignupRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
#include "MenuHandler.h"
bool SignupRequestHandler::IsValid(unsigned char status)
{
    return status == SIGNUP;
}

Responce* SignupRequestHandler::HandlerRequest(Request* req)
{
    auto ret = new SignUpResponce();
    Buffer retBuffer;
	http::json::JsonObject retJsonMessage;
	ret->next = new MenuHandler();
	
	SignUpRequest* signupRequest = (SignUpRequest*)req;
	retBuffer.status = OK;
	auto& instence = RequsetFactory::getInstence();
	instence.getLoginManager().Signup(signupRequest->_username, signupRequest->_password, signupRequest->_email);
	
	retBuffer.sizeOfData = 0;
	retBuffer.data = nullptr;
	ret->buffer = retBuffer;
	return ret;
}

Request* SignupRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new SignUpRequest(JsonRequestPacketDeserializer::deserializeSignUpRequest(buffer));
}
