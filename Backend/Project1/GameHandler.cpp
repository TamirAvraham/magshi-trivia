#include "GameHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "RequsetFactory.h"
#include "JsonSirealizer.h"
#include "AdminRoomHandler.h"

using Json = http::json::JsonObject;
bool GameHandler::IsValid(unsigned char status)
{
	try
	{
		char secondDigit = std::to_string(((int)status))[0];
		return secondDigit == QUESTION_CHAR;
	}
	catch (...)
	{
		return false;
	}
}

Responce* GameHandler::HandlerRequest(Request* req)
{
	switch (req->id)
	{
		
	default:
		return nullptr;
	}
}

Request* GameHandler::GetRequestFromBuffer(const Buffer& buffer)
{
	switch (buffer.status)
	{
	case getAnswers:
		return new GetAnswersRequest(JsonRequestPacketDeserializer::deserializeGetAnswersRequest(buffer));
	case getCorrectAnswer:
		return new GetCorrectAnswerRequest(JsonRequestPacketDeserializer::deserializeGetCorrectAnswerRequest(buffer));
	case submitAnswer:
		return new SubmitAnswerRequest(JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(buffer));
	case getUserPoints:
		return new GetUserPointsRequest(JsonRequestPacketDeserializer::deserializeGetUserPointsRequest(buffer));
	case getQuestion:
		return new GetQuestionRequest(JsonRequestPacketDeserializer::deserializeGetQuestionRequest(buffer));
	default:
		return nullptr;
	}
}

inline Responce GameHandler::handleGetAnswersRequest(const GetAnswersRequest* request) const
{
	Responce ret;
	auto& gameManger = RequsetFactory::getInstence().getGameManger();

	auto answers=gameManger.getGame(request->gameId).getAnswers(request->question);
	auto answersAsJsonVectorString = JsonSirealizer::getVectorAsString(answers);

	Json dataAsJson;
	dataAsJson.insert({ {"answers"} ,{answersAsJsonVectorString} });
	auto dataAsString = dataAsJson.ToString();

	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = new GameHandler();
	
	return ret;
}

inline Responce GameHandler::handleSubmitAnswerRequest(const SubmitAnswerRequest* request) const
{
	Responce ret;
	auto& gameManger = RequsetFactory::getInstence().getGameManger();
	auto& user = RequsetFactory::getInstence().getLoginManager().getUser(request->username);

	auto correctAnswer = gameManger.getGame(request->gameId).submitAnswer(user, request->question, request->answer, request->timeToAnswer);
	

	Json dataAsJson;
	dataAsJson.insert({ {"correctAnswer"} , {correctAnswer ? "true" : "false"} });

	auto dataAsString = dataAsJson.ToString();
	
	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = new GameHandler();

	return ret;
}

inline Responce GameHandler::handleGetCorrectAnswerRequest(const GetCorrectAnswerRequest* request) const
{


	Responce ret;
	auto& gameManger = RequsetFactory::getInstence().getGameManger();

	auto answer = gameManger.getGame(request->gameId).getCorrectAnswer(request->question);
	

	Json dataAsJson;
	dataAsJson.insert({ {"answer"} ,{answer} });
	auto dataAsString = dataAsJson.ToString();

	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = new GameHandler();

	return ret;
}

inline Responce GameHandler::handleGetQuestionRequest(const GetQuestionRequest* request) const
{
	Responce ret;
	auto& factory = RequsetFactory::getInstence();
	auto& gameManger = factory.getGameManger();
	auto& user = factory.getLoginManager().getUser(request->username);

	auto question = gameManger.getGame(request->gameId).getQuestionForUser(user);
	std::vector<std::string> answers;

	if (question!="")
	{
		answers = gameManger.getGame(request->gameId).getAnswers(question);
	}
	
	auto answersAsJsonVectorString = JsonSirealizer::getVectorAsString(answers);

	Json dataAsJson;
	dataAsJson.insert({ {"question"}, { question }});
	dataAsJson.insert({ {"answers"} ,{answersAsJsonVectorString} });
	auto dataAsString = dataAsJson.ToString();

	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = new GameHandler();

	return ret;
}

inline Responce GameHandler::handleGetUserPointsRequest(const GetUserPointsRequest* request) const
{
	Responce ret;
	auto& factory = RequsetFactory::getInstence();
	auto& gameManger = factory.getGameManger();
	auto& user = factory.getLoginManager().getUser(request->username);
	auto& game = gameManger.getGame(request->gameId);
	auto& roomManger = factory.getRoomsManager();
	auto points = game.getPlayerPoints(user);

	Json dataAsJson;
	dataAsJson.insert({ {"points"},{std::to_string(points)} });
	auto dataAsString = dataAsJson.ToString();

	auto buffer = Buffer{
		.status = OK,
		.sizeOfData = static_cast<unsigned int>(dataAsString.size()),
		.data = new char[dataAsString.size() + 1]
	};

	std::copy(dataAsString.begin(), dataAsString.end(), buffer.data);
	buffer.data[dataAsString.size()] = '\0';

	ret.buffer = buffer;
	ret.next = roomManger.getRoom(game.getRoomId()).isAdmin(user) ? new AdminRoomHandler() : new RoomMemberHandler();
	
	return ret;
}
