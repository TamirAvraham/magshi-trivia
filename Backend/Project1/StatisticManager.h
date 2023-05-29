#pragma once
#include "SqliteDatabase.h"

class StatisticManager
{
public:
	std::vector<int> getUserGameStatistic(std::string username, SqliteDataBase db);
	std::vector <Game_Statistic> getTopFive(SqliteDataBase db);
};

