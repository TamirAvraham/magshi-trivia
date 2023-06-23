#pragma once
#include "SqliteDatabase.h"
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

struct QuestionsData
{
	std::vector<std::string> answered_questions;
	
	int correct_answer_count;
	int wrong_answer_count;
	int average_time_per_question;
};

class Game
{
	Game();
	std::string getQuestionForUser(const LoggedUser& user);
	std::vector<std::string> getAnswers(const std::string question);
	std::string getCorrectAnswer(const std::string question);
	int getPlayerPoints(const LoggedUser& user);
private:
	std::vector<Question> questions;
	std::map<LoggedUser, QuestionsData> usersAndTheirData;
};

