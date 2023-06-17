#include "StatisticManager.h"

Statistic StatisticManager::getUserGameStatistic(std::string username, SqliteDataBase& db)
{
    auto test= db.getUserGameStatistic(username);
    return test[0];
}

std::vector<Game_Statistic> StatisticManager::getTopFive(SqliteDataBase& db)
{
    return db.getTopFive();
}
