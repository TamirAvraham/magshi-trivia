#include "IRequestHandler.h"
#include "MenuHandler.h"
#define StatHandlerMethod(param)  inline param##Responce handle##param##Request(const param##Request request) const
class StatisticsHandler: public IRequestHandler
{
public:
	// Inherited via IRequestHandler
	virtual bool IsValid(unsigned char status) override;
	virtual Responce* HandlerRequest(Request* req) override;
	virtual Request* GetRequestFromBuffer(const Buffer& buffer) override;
private:
	inline GetTopPlayersResponce handleGetTopPlayersRequest(const GetTopPlayersRequest request) const;
	inline GetPlayerStatisticsResponce handleGetPlayerStatisticsRequest(const GetPlayerStatisticsRequest request) const;
};
