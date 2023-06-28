#include "SqliteDataBase.h"

SqliteDataBase::SqliteDataBase()
{
	if (!open())
	{
		std::cout << "Failed to open the database file!\n";
		exit(EXIT_FAILURE);
	}
}

// Open (or creates) the database file
bool SqliteDataBase::open()
{
	if (sqlite3_open(DB_FILE_NAME, &_database) != SQLITE_OK)
	{
		_database = nullptr;
		std::cout << "Failed to open DB\n";
		return false;
	}
	sendSQL(CREATE_USERS_TABLE, nullptr, nullptr);
	sendSQL(CREATE_QUESTIONS_TABLE, nullptr, nullptr);
	sendSQL(CREATE_STATISTICS_TABLE, nullptr, nullptr);
	sendSQL(CREATE_GAME_RECORDS_TABLE, nullptr, nullptr);

	sendSQL(ADD_QUESTION_1, nullptr, nullptr);
	sendSQL(ADD_QUESTION_2, nullptr, nullptr);
	sendSQL(ADD_QUESTION_3, nullptr, nullptr);
	sendSQL(ADD_QUESTION_4, nullptr, nullptr);
	sendSQL(ADD_QUESTION_5, nullptr, nullptr);
	sendSQL(ADD_QUESTION_6, nullptr, nullptr);
	sendSQL(ADD_QUESTION_7, nullptr, nullptr);
	sendSQL(ADD_QUESTION_8, nullptr, nullptr);
	sendSQL(ADD_QUESTION_9, nullptr, nullptr);
	sendSQL(ADD_QUESTION_10, nullptr, nullptr);
	return true;
}
bool SqliteDataBase::doesUserExist(std::string username)
{
	std::vector<User> users;
	sendSQL(("SELECT * FROM users WHERE username  = '" + username + "';").c_str(), callbackUser, &users);
	return users.size() > 0;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	std::vector<User> users;
	sendSQL(("SELECT * FROM users WHERE username  = '" + username + "' AND password = '" + password + "';").c_str(), callbackUser, &users);
	return users.size() > 0;
}

void SqliteDataBase::addNewUser(std::string username, std::string password, std::string email)
{
	sendSQL(("INSERT INTO users VALUES ('" + username + "', '" + password + "', '" + email + "');").c_str(), nullptr, nullptr);	// might change to INSERT OR IGNORE
}

std::string SqliteDataBase::getQuestion()
{
	std::vector<Question> questions;
	sendSQL("SELECT * FROM questions;", callbackQuestion, &questions);
	srand(time(0));
	return questions[rand() % questions.size()].question;
}

std::vector<Question> SqliteDataBase::getQuestions()
{
	std::vector<Question> questions;
	sendSQL("SELECT * FROM questions;", callbackQuestion, &questions);
	return questions;
}

std::string SqliteDataBase::getCorrectAnswer(std::string question)
{
	std::vector<Question> questions;
	sendSQL(("SELECT * FROM questions WHERE question = '" + question + "';").c_str(), callbackQuestion, &questions);
	
	// If no questions or multiple questions with same text (Even though question has the 'UNIQUE' tag in database so second option is impossible the code can never be too safe)
	if (questions.size() != 1)
	{
		throw std::invalid_argument("invalid argument");
	}
	return questions.front().correct_answer;
}

//Loops with const value are not input dependant so this function is O(1)
std::vector<std::string> SqliteDataBase::getAllAnswers(std::string question)
{
	std::vector<Question> questions;
	sendSQL(("SELECT * FROM questions WHERE question = '" + question + "';").c_str(), callbackQuestion, &questions);

	// If no questions or multiple questions with same text (Even though question has the 'UNIQUE' tag in database so second option is impossible the code can never be too safe)
	if (questions.size() != 1)
	{
		throw std::invalid_argument("invalid argument");
	}
	std::vector<std::string> ret;
	bool addedCorrect = false;
	int addedWrong = 0;
	
	srand(time(0));
	for (int i = 0; i < 4; i++)
	{
		if (!addedCorrect)
		{
			if (addedWrong == 3)
			{
				ret.push_back(questions.front().correct_answer);
				addedCorrect = true;	// technically this is a useless line but we'll keep it for easiness of understanding the code
			}
			else
			{
				if (rand() % 2 == 0)
				{
					ret.push_back(questions.front().correct_answer);
					addedCorrect = true;
				}
				else
				{
					ret.push_back(questions.front().wrong_answers[addedWrong++]);
				}
			}
		}
		else
		{
			ret.push_back(questions.front().wrong_answers[addedWrong++]);
		}
	}
	return ret;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	std::vector<Statistic> stats;
	sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &stats);
	return (float)((float)stats.front().total_seconds / (float)stats.front().total_answers);
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	std::vector<Statistic> stats;
	sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &stats);
	return stats.front().correct_answers;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	std::vector<Statistic> stats;
	sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &stats);
	return stats.front().total_answers;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	std::vector<Statistic> stats;
	sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &stats);
	return stats.front().total_games;
}

std::vector<Statistic> SqliteDataBase::getUserGameStatistic(std::string username)
{
	std::vector<Statistic> gameStats;
	sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &gameStats);
	if (gameStats.empty())
	{
		createUserStats(username);
		sendSQL(("SELECT * FROM statistics WHERE user = '" + username + "';").c_str(), callbackStatistic, &gameStats);
	}
	return gameStats;
}

std::vector<Game_Statistic> SqliteDataBase::getTopFive()
{
	std::vector<Game_Statistic> gameStats;
	sendSQL("SELECT * FROM game_records ORDER BY points DESC LIMIT 5;", callbackGameStatistic, &gameStats);
	return gameStats;
}

void SqliteDataBase::updateUserStats(const GameResult& result, const int& questionCount)
{
	getUserGameStatistic(result.username);
	sqlite3_stmt* stmt;
	std::string sql = "UPDATE statistics SET total_answers = total_answers + ?, "
		"correct_answers = correct_answers + ?, "
		"total_seconds_to_answer = total_seconds_to_answer + ?, "
		"total_games_played = total_games_played + 1 "
		"WHERE user = ?;";
	int rc = sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		std::cout << std::string(sqlite3_errmsg(_database)) << std::endl;
		return;
	}

	
	sqlite3_bind_int(stmt, 1, questionCount);
	sqlite3_bind_int(stmt, 2, result.correctAnswerCount);
	sqlite3_bind_int(stmt, 3, result.avgAnswerTime);
	sqlite3_bind_text(stmt, 4, result.username.c_str(), -1, SQLITE_STATIC);

	// Execute the SQL statement
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		std::cout << std::string(sqlite3_errmsg(_database)) << std::endl;

	}

	// Finalize the statement
	sqlite3_finalize(stmt);

	// Update the game_records table
	sql = "INSERT OR REPLACE INTO game_records (name_of_user, points) "
		"VALUES (?, ?);";
	rc = sqlite3_prepare_v2(_database, sql.c_str(), -1, &stmt, nullptr);
	if (rc != SQLITE_OK)
	{
		std::cout << std::string(sqlite3_errmsg(_database)) << std::endl;
		return;
	}

	
	sqlite3_bind_text(stmt, 1, result.username.c_str(), -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, result.points);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE)
	{
		
	}

	// Finalize the statement
	sqlite3_finalize(stmt);
}


void SqliteDataBase::createUserStats(const std::string& username)
{
	sendSQL(("INSERT INTO statistics (user, total_answers, correct_answers, total_seconds_to_answer, total_games_played) VALUES (\'"+username+"\', 0, 0, 0, 0); ").c_str(), nullptr, nullptr);
	sendSQL(("INSERT INTO game_records (name_of_user, points)VALUES (\'" + username + "\', 0 );").c_str(), nullptr, nullptr);
}

bool SqliteDataBase::sendSQL(const char* sqlCommand, int (*callback)(void*, int, char**, char**), void* data)
{
	if (sqlite3_exec(_database, sqlCommand, callback, data, nullptr) != SQLITE_OK) //Send SQL command
	{
		std::cout << "Failure: " << sqlCommand << std::endl;
		return false;
	}
	return true;
}

int callbackUser(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 0)	// No argument
		return 0;
	std::string name(argv[0]);
	std::string password(argv[1]);
	std::string email(argv[2]);
	User newUser;
	newUser.username = name;
	newUser.password = password;
	newUser.email = email;
	((std::vector<User>*)data)->push_back(newUser);	// Adding User to the list
	return 0;
}

int callbackQuestion(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 0)	// No argument
		return 0;
	std::string question(argv[0]);
	std::string correct_answer(argv[1]);
	std::string wrong_answer_1(argv[2]);
	std::string wrong_answer_2(argv[3]);
	std::string wrong_answer_3(argv[4]);

	Question newQuestion;
	newQuestion.question = question;
	newQuestion.correct_answer = correct_answer;
	newQuestion.wrong_answers[0] = wrong_answer_1;
	newQuestion.wrong_answers[1] = wrong_answer_2;
	newQuestion.wrong_answers[2] = wrong_answer_3;
	
	std::vector<Question>* dataAsVec = (std::vector<Question>*)(data);
	dataAsVec->push_back(newQuestion);	// Adding Question to the list
	return 0;
}

int callbackStatistic(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 0)	// No argument
		return 0;
	std::string username(argv[0]);
	std::string total_answers(argv[1]);
	std::string correct_asnwers(argv[2]);
	std::string total_seconds(argv[3]);
	std::string total_games_played(argv[4]);

	Statistic newStatistic;
	newStatistic.user = username;
	newStatistic.total_answers =  std::stoi(total_answers);
	newStatistic.correct_answers =  std::stoi(correct_asnwers);
	newStatistic.total_seconds =  std::stoi(total_seconds);
	newStatistic.total_games =  std::stoi(total_games_played);
	
	((std::vector<Statistic>*)data)->push_back(newStatistic);	// Adding Statistic to the list
	return 0;
}

int callbackGameStatistic(void* data, int argc, char** argv, char** azColName)
{
	if (argc == 0)	// No argument
		return 0;
	std::string username(argv[0]);
	std::string points(argv[1]);
	
	Game_Statistic newGameStatistic;
	newGameStatistic.user = username;
	newGameStatistic.points = std::stoi(points);

	((std::vector<Game_Statistic>*)data)->push_back(newGameStatistic);	// Adding GameStatistic to the list
	return 0;
}
