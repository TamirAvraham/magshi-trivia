#pragma once
#include "IRequestHandler.h"
#define GameHandlerMethod(param) inline Responce handle##param##Request(const param##Request* request) const;
class GameHandler:public IRequestHandler
{
public:

	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;

	inline Responce handleGetAnswersRequest(const GetAnswersRequest* request) const;
	inline Responce handleSubmitAnswerRequest(const SubmitAnswerRequest* request) const;
	inline Responce handleGetCorrectAnswerRequest(const GetCorrectAnswerRequest* request) const;
	inline Responce handleGetQuestionRequest(const GetQuestionRequest* request) const;
	inline Responce handleGetUserPointsRequest(const GetUserPointsRequest* request) const;
};

