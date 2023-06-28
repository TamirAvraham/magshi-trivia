#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include "JsonObject.h"
#include "GameManager.h"
#include <list>
#include <vector>
#include <string>

constexpr auto DB_FILE_NAME = "GameDataBase.sqlite";
constexpr auto CREATE_USERS_TABLE = "CREATE TABLE IF NOT EXISTS users ( username TEXT UNIQUE NOT NULL, password TEXT NOT NULL, email TEXT NOT NULL);";
constexpr auto CREATE_QUESTIONS_TABLE = "CREATE TABLE IF NOT EXISTS questions (question TEXT UNIQUE NOT NULL, correct_answer TEXT NOT NULL, wrong_answer_1 TEXT NOT NULL, wrong_answer_2 TEXT NOT NULL, wrong_answer_3 TEXT NOT NULL);";
constexpr auto CREATE_STATISTICS_TABLE = "CREATE TABLE IF NOT EXISTS statistics (user TEXT PRIMARY KEY, total_answers INTEGER NOT NULL, correct_answers INTEGER NOT NULL, total_seconds_to_answer INTEGER NOT NULL, total_games_played INTEGER NOT NULL, FOREIGN KEY (user) REFERENCES users(username));";
constexpr auto CREATE_GAME_RECORDS_TABLE = "CREATE TABLE IF NOT EXISTS game_records (name_of_user TEXT PRIMARY KEY, points INTEGER, FOREIGN KEY (name_of_user) REFERENCES users(username));";

constexpr auto ADD_QUESTION_1 = "INSERT OR IGNORE INTO questions VALUES('Cube root of -1 is...','-1','i','I','-i');";
constexpr auto ADD_QUESTION_2 = "INSERT OR IGNORE  INTO questions VALUES('What is a watermellon?','Berry','Vegetable','Chocolate','Tree');";
constexpr auto ADD_QUESTION_3 = "INSERT OR IGNORE  INTO questions VALUES('What is the correct answer?','Correct Answer','I am','Correct','Answer');";
constexpr auto ADD_QUESTION_4 = "INSERT OR IGNORE  INTO questions VALUES('Will you answer this question correct?','I just did','Probably no','Maybe','Not(Not(Not(Not(Not(Not(No)))))');";
constexpr auto ADD_QUESTION_5 = "INSERT OR IGNORE  INTO questions VALUES('Am I dead or alive','Neither, you''re a machine','Dead','Alive','If god made you then yes');";
constexpr auto ADD_QUESTION_6 = "INSERT OR IGNORE  INTO questions VALUES('What is the meaning of life?','Whatever you want it to be,','108 105 102 101 ','47','Programming');";
constexpr auto ADD_QUESTION_7 = "INSERT OR IGNORE  INTO questions VALUES('Why did the chicken cross the road?', 'To get to the other side', 'To get to an idiots house', 'To escape the farm', 'To go eat at KFC');";
constexpr auto ADD_QUESTION_8 = "INSERT OR IGNORE  INTO questions VALUES('What is the best selling game?', 'Minecraft', 'Tetris', 'GTA V', 'The Elder Scrolls V: Skyrim');";
constexpr auto ADD_QUESTION_9 = "INSERT OR IGNORE  INTO questions VALUES('What is the fastest thing?', 'Diarrhea', 'Light', 'Sound', 'Your friend when you gave him 3 seconds to eat your food'); ";
constexpr auto ADD_QUESTION_10 = "INSERT OR IGNORE  INTO questions VALUES('What is the chemistry formula for simple alcohol?','C2H5OH','ROH','H2O','SiH6O9');";

struct Game_Statistic;
struct Statistic;
struct Question
{
	std::string question;
	std::string correct_answer;
	std::string wrong_answers[3];

	bool operator==(const Question& other) const {
		return question == other.question && correct_answer == other.correct_answer;
	}
};
class SqliteDataBase : public IDatabase
{
public:
	static SqliteDataBase& GetInstance() {
		static SqliteDataBase instance;
		return instance;
	}
	// User related Functions
	bool open();
	virtual bool doesUserExist(std::string username) override;
	virtual bool doesPasswordMatch(std::string username, std::string password) override;
	virtual void addNewUser(std::string username, std::string password, std::string email) override;

	// Question related functions
	std::string getQuestion();
	std::vector<Question> getQuestions();
	std::string getCorrectAnswer(std::string question);
	std::vector<std::string> getAllAnswers(std::string question);

	// Statistic related functions
	float getPlayerAverageAnswerTime(std::string username);
	int getNumOfCorrectAnswers(std::string username);
	int getNumOfTotalAnswers(std::string username);
	int getNumOfPlayerGames(std::string username);

	// Game_Statistic related functions
	std::vector<Statistic> getUserGameStatistic(std::string username);
	std::vector <Game_Statistic> getTopFive();


	void updateUserStats(const GameResult& result,const int& questionCount);
private:
	//stats helpers
	void createUserStats(const std::string& username);


	SqliteDataBase();
	bool sendSQL(const char* sqlCommand, int (*callback)(void*, int, char**, char**), void* data);
	sqlite3* _database;
};

struct User
{
	std::string username;
	std::string password;
	std::string email;
};



struct Statistic
{
	std::string user;
	int total_answers;
	int correct_answers;
	int total_seconds;
	int total_games;

	std::string toString() const {
		http::json::JsonObject ret;
		ret.insert({ "user",{user} });
		ret.insert({ "total_games",{std::to_string(total_games)} });
		ret.insert({ "total_answers",{std::to_string(total_answers)} });
		ret.insert({ "total_seconds",{std::to_string(total_seconds)} });
		ret.insert({ "correct_answers",{std::to_string(correct_answers)} });
		return ret.ToString();
	}
};

struct Game_Statistic
{
	std::string user;
	int points;
	std::string toString() const {
		http::json::JsonObject ret;
		ret.insert({ "user", { user } });
		ret.insert({ "points",{std::to_string(points)} });
		return ret.ToString();
	}
};

int callbackUser(void* data, int argc, char** argv, char** azColName);
int callbackQuestion(void* data, int argc, char** argv, char** azColName);
int callbackStatistic(void* data, int argc, char** argv, char** azColName);
int callbackGameStatistic(void* data, int argc, char** argv, char** azColName);
