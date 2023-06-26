#include "GameManager.h"

Game::Game(const Room& room):roomId(room.getId())
{
	questions = SqliteDataBase::GetInstance().getQuestions();
	auto rng = std::default_random_engine{ std::random_device{}()};
	std::shuffle(std::begin(questions), std::end(questions), rng);

    const auto& roomUsers = room.getUsers();
    for (const auto& user : roomUsers) {
        usersAndTheirData.insert({ user, QuestionsData() });
    }
}

std::string Game::getQuestionForUser(const LoggedUser& user) const
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
            usersAndTheirData.at(user).answered_questions.push_back(question.question);
            return question.question;
        }
    }
    return "";
}

std::vector<std::string> Game::getAnswers(const std::string& question) const
{
	return SqliteDataBase::GetInstance().getAllAnswers(question);
}

std::string Game::getCorrectAnswer(const std::string& question) const
{
	return SqliteDataBase::GetInstance().getCorrectAnswer(question);
}

bool Game::submitAnswer(const LoggedUser& user, const std::string& qusetion, const std::string& answer, const int& duration ) 
{
    auto correctAnswer = getCorrectAnswer(qusetion);
    auto& userData = usersAndTheirData.at(user);

    bool ret = correctAnswer == answer;
    ret ? userData.correct_answer_count++ : userData.wrong_answer_count++;

    userData.answered_questions.push_back(qusetion);
    userData.total_time += duration;
    return ret;
}

int Game::getPlayerPoints(const LoggedUser& user) const
{
    
    try
    {
        return (POINTS_PER_CORRECT_ASNWER * 100 - POINTS_PER_CORRECT_ASNWER * usersAndTheirData.at(user).average_time_per_question) * (1 + usersAndTheirData.at(user).correct_answer_count / 10.0);
    }
    catch (...)
    {
        return 0;
    }
    
}

int Game::getRoomId() const
{
    return roomId;
}

std::vector<GameResult> Game::getGameResults() const
{
    std::vector<GameResult> ret;
    for (const auto& userData : usersAndTheirData) {
        ret.push_back(getResultForUser(userData));
    }
    return ret;
}

GameResult Game::getResultForUser(const std::pair<LoggedUser, QuestionsData>& userData) const
{
    GameResult ret;
    ret.avgAnswerTime = userData.second.total_time / (double)userData.second.answered_questions.size();
    ret.correctAnswerCount = userData.second.correct_answer_count;
    ret.points = getPlayerPoints(userData.first);
    ret.username = userData.first.username;
    return ret;
}

Game& GameManger::getGame(const int& id)
{
    return games[id];
}

int GameManger::createNewGame(const Room& room)
{
    Game game(room);
    
    games.push_back(game);
    return games.size() - 1;
}

void GameManger::deleteGame(const int& id)
{
    try
    {
        games.erase(games.begin() + id);
    }
    catch (const std::exception&)
    {
        // if we went out of range well then the game doesnt exist so no need to delete
    }
}

std::string GameResult::toString() const
{
    http::json::JsonObject ret;
    ret.insert({ {"averageAnswerTime "},{std::to_string(avgAnswerTime)} });
    ret.insert({ {"correctAnswerCount"},{std::to_string(correctAnswerCount)} });
    ret.insert({ {"points"},{std::to_string(points)} });
    ret.insert({ {"username"},{username}});
    return ret.ToString();
}
