#include "GameManager.h"

Game::Game()
{
	questions = SqliteDataBase::GetInstance().getQuestions();
	auto rng = std::default_random_engine{ std::random_device{}()};
	std::shuffle(std::begin(questions), std::end(questions), rng);
}

std::string Game::getQuestionForUser(const LoggedUser& user)
{
    for (const auto& question : questions)
    {
        bool questionAnswered = false;
        for (const auto& userData : usersAndTheirData)
        {
            const QuestionsData& data = userData.second;
            if (std::find(data.answered_questions.begin(), data.answered_questions.end(), question.question) != data.answered_questions.end())
            {
                questionAnswered = true;
                break;
            }
        }
        if (!questionAnswered)
        {
            usersAndTheirData[user].answered_questions.push_back(question.question);
            return question.question;
        }
    }
    return "";
}

std::vector<std::string> Game::getAnswers(const std::string question)
{
	return SqliteDataBase::GetInstance().getAllAnswers(question);
}

std::string Game::getCorrectAnswer(const std::string question)
{
	return SqliteDataBase::GetInstance().getCorrectAnswer(question);
}

int Game::getPlayerPoints(const LoggedUser& user)
{
    if (std::find(usersAndTheirData.begin(), usersAndTheirData.end(), user) != usersAndTheirData.end())
        return (POINTS_PER_CORRECT_ASNWER * 100 - POINTS_PER_CORRECT_ASNWER * usersAndTheirData[user].average_time_per_question) * (1 + usersAndTheirData[user].correct_answer_count / 10.0);
    return NULL;
}
