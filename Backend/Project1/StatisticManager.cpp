#include "StatisticManager.h"

Statistic StatisticManager::getUserGameStatistic(std::string username, SqliteDataBase db)
{
    return db.getUserGameStatistic(username)[0];
}

std::vector<Game_Statistic> StatisticManager::getTopFive(SqliteDataBase db)
{
    return db.getTopFive();
}
