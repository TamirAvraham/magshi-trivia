#include "StatisticManager.h"

std::vector<int> StatisticManager::getUserGameStatistic(std::string username, SqliteDataBase db)
{
    return db.getUserGameStatistic(username);
}

std::vector<Game_Statistic> StatisticManager::getTopFive(SqliteDataBase db)
{
    return db.getTopFive();
}
