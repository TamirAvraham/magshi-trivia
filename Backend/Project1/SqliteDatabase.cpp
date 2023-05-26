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
	std::list<User> users;
	sendSQL(("SELECT * FROM users WHERE username  = '" + username + "';").c_str(), callbackUser, &users);
	return users.size() > 0;
}

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string password)
{
	std::list<User> users;
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
	std::list<Question> questions;
	sendSQL(("SELECT * FROM questions WHERE question = '" + question + "';").c_str(), callbackQuestion, &questions);
	
	// If no questions or multiple questions with same text (Even though question has the 'UNIQUE' tag in database so second option is impossible the code can never be too safe)
	if (question.size() != 1)
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

	((std::vector<Question>*)data)->push_back(newQuestion);	// Adding User to the list
	return 0;
}
