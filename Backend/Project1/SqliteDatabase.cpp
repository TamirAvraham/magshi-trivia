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
	std::list<Question> questions;
	sendSQL(("SELECT * FROM questions WHERE question = '" + question + "';").c_str(), callbackQuestion, &questions);

	// If no questions or multiple questions with same text (Even though question has the 'UNIQUE' tag in database so second option is impossible the code can never be too safe)
	if (question.size() != 1)
	{
		throw std::invalid_argument("invalid argument");
	}
	std::vector<std::string> ret;
	bool doneCorrect = false;
	int doneWrong = 0;
	
	srand(time(0));
	for (int i = 0; i < 4; i++)
	{
		if (!doneCorrect)
		{
			if (doneWrong == 3)
			{
				ret.push_back(questions.front().correct_answer);
				doneCorrect = true;	// technically this is a useless line but we'll keep it for easiness of understanding the code
			}
			else
			{
				if (rand() % 2 == 0)
				{
					ret.push_back(questions.front().correct_answer);
					doneCorrect = true;
				}
				else
				{
					ret.push_back(questions.front().wrong_answers[doneWrong++]);
				}
			}
		}
		else
		{
			ret.push_back(questions.front().wrong_answers[doneWrong++]);
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

std::vector<int> SqliteDataBase::getUserGameStatistic(std::string username)
{
	std::vector<Game_Statistic> gameStats;
	sendSQL(("SELECT * FROM game_records WHERE name_of_user = '" + username + "';").c_str(), callbackStatistic, &gameStats);
	std::vector<int> ret;
	for (int i = 0; i < gameStats.size(); i++)
		ret.push_back(gameStats[i].points);
	return ret;
}

std::vector<Game_Statistic> SqliteDataBase::getTopFive()
{
	std::vector<Game_Statistic> gameStats;
	sendSQL("SELECT * FROM game_records ORDER BY points DESC LIMIT 5;", callbackStatistic, &gameStats);
	return gameStats;
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
	((std::list<User>*)data)->push_back(newUser);	// Adding User to the list
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

	((std::vector<Question>*)data)->push_back(newQuestion);	// Adding Question to the list
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
