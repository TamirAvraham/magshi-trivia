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
    auto ret = new LoginResponce();
    Buffer retBuffer;
	ret->next = new MenuHandler();
	
	LoginRequest* loginRequest = (LoginRequest*)req;
	retBuffer.status = OK;
	auto& instence = RequsetFactory::getInstence();
	instence.getLoginManager().Login(loginRequest->_username, loginRequest->_password);

	retBuffer.sizeOfData = 0;
	retBuffer.data = new char[1];
	retBuffer.data[0] = '\0';
	ret->buffer = retBuffer;
	
    return ret;
}

Request* LoginRequestHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	return new LoginRequest(JsonRequestPacketDeserializer::deserializeLoginRequest(buffer));
}
