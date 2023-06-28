#pragma once
#include <random>
#include "loggedUser.h"
#include "JsonSirealizer.h"

#define POINTS_PER_CORRECT_ASNWER 1000

//struct QuestionAndAnswers
//{
//	std::string question;
//	std::vector<std::string> all_asnwers;
//	std::string correct_answer;
//
//	http::json::JsonObject toJson()const {
//		http::json::JsonObject object;
//		object.insert({ "question",{question} });
//		object.insert({ "all_answers",{JsonSirealizer::getVectorAsString(all_asnwers)} });
//		object.insert({ "correct_answer",{correct_answer} });
//		return object;
//	}
//
//	std::string toString()const {
//		return toJson().ToString();
//	}
//};
struct Question;
struct QuestionsData
{
	std::vector<std::string> answered_questions;
	
	int correct_answer_count;
	int wrong_answer_count;
	int average_time_per_question;

	int total_time;
	bool operator==(const QuestionsData& other) const
	{
		return answered_questions == other.answered_questions && correct_answer_count == other.correct_answer_count && wrong_answer_count == other.wrong_answer_count && average_time_per_question == other.average_time_per_question;
	}
};
struct GameResult
{
	std::string username;
	int avgAnswerTime;
	int correctAnswerCount;
	int points;
	std::string toString()const;
};
class Game
{
public:
	Game(const Room& room);
	std::string getQuestionForUser(const LoggedUser& user)const;
	std::vector<std::string> getAnswers(const std::string& question)const;
	std::string getCorrectAnswer(const std::string& question)const;
	bool submitAnswer(const LoggedUser& user, const std::string& question, const std::string&  answer, const int& duration );
	int getPlayerPoints(const LoggedUser& user)const;
	int getRoomId()const;
	std::vector<GameResult> getGameResults()const;
private:
	int roomId;
	std::vector<Question> questions;
	mutable std::map<LoggedUser, QuestionsData> usersAndTheirData;
	GameResult getResultForUser(const std::pair<LoggedUser, QuestionsData>& userData)const;
public:

	bool operator==(const Game& other) const {
		if (usersAndTheirData.size() != other.usersAndTheirData.size()) {
			return false;
		}

		// Iterate over each key-value pair and check for equality
		for (const auto& pair : usersAndTheirData) {
			const auto& user = pair.first;
			const auto& data = pair.second;

			// Check if the user exists in the other Game object
			if (other.usersAndTheirData.count(user) == 0) {
				return false;
			}

			// Compare the QuestionsData objects
			if (data.correct_answer_count != other.usersAndTheirData.at(user).correct_answer_count ||
				data.wrong_answer_count != other.usersAndTheirData.at(user).wrong_answer_count ||
				data.average_time_per_question != other.usersAndTheirData.at(user).average_time_per_question ||
				data.answered_questions != other.usersAndTheirData.at(user).answered_questions) {
				return false;
			}
		}

		return true;
	}
};
class GameManger {
private:
	std::vector<Game> games;
	
public:
	Game& getGame(const int& id);
	int createNewGame(const Room& room);
	void deleteGame(const int& id);
};
