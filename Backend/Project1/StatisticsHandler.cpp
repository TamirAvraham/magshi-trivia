
#include "StatisticsHandler.h"
#include "RequsetFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "SqliteDatabase.h"
#include "JsonSirealizer.h"
#define retrunHandler(name) return new name##Responce(handle##name##Request((name##Request)(*req)));
bool StatisticsHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == STATISTICS_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* StatisticsHandler::HandlerRequest(Request* req)
{
	switch (req->id)
	{
	case getPlayerStatistics:
		return new GetPlayerStatisticsResponce(handleGetPlayerStatisticsRequest((GetPlayerStatisticsRequest*)(req)));
	case getTopPlayers:
		return new GetTopPlayersResponce(handleGetTopPlayersRequest((GetTopPlayersRequest*)(req)));
	default:
		return nullptr;
	}
}

Request* StatisticsHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case getPlayerStatistics:
		return new GetPlayerStatisticsRequest(JsonRequestPacketDeserializer::deserializeGetPlayerStatisticsRequest(buffer));
	case getTopPlayers:
		return new GetTopPlayersRequest(JsonRequestPacketDeserializer::deserializeGetTopPlayersRequest(buffer));
	default:
		return nullptr;
	}
}

inline GetTopPlayersResponce StatisticsHandler::handleGetTopPlayersRequest(GetTopPlayersRequest* request) const
{
	GetTopPlayersResponce ret;
	auto topPlayers = RequsetFactory::getInstence().getStatManager().getTopFive(SqliteDataBase::GetInstance());
	auto bufferData = JsonSirealizer::getVectorAsString(topPlayers);
	auto buffer = Buffer{ 
		.status = OK,
		.sizeOfData = (unsigned int)bufferData.size(),
		.data = new char[bufferData.size() + 1]
	};
	std::copy(bufferData.begin(), bufferData.end(), buffer.data);
	buffer.data[bufferData.size()] = '\0';
	ret.buffer = buffer;
	ret.next = new MenuHandler();
	return ret;
}

inline GetPlayerStatisticsResponce StatisticsHandler::handleGetPlayerStatisticsRequest(GetPlayerStatisticsRequest* request) const
{
	GetPlayerStatisticsResponce ret;
	auto statistic = RequsetFactory::getInstence().getStatManager().getUserGameStatistic(request->playerUsername, SqliteDataBase::GetInstance());
	auto bufferData = statistic.toString();
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = (unsigned int)bufferData.size(),
		.data = new char[bufferData.size() + 1]
	};
	std::copy(bufferData.begin(), bufferData.end(), buffer.data);
	buffer.data[bufferData.size()] = '\0';
	ret.buffer = buffer;
	ret.next = new MenuHandler();
	return ret;
}
