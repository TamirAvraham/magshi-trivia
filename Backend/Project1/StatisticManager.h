#pragma once
#include "SqliteDatabase.h"

class StatisticManager
{
public:
	Statistic getUserGameStatistic(std::string username, SqliteDataBase db);
	std::vector <Game_Statistic> getTopFive(SqliteDataBase db);
};

