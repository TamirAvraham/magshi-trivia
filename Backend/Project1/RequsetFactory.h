#pragma once
#include "GameManager.h"
#include "LoginManager.h"
#include "RoomsManger.h"
#include "StatisticManager.h"
#include "IRequestHandler.h"
class RequsetFactory
{
public:
	//this is the singleton part
	static RequsetFactory& getInstence() {
		static RequsetFactory instence;
		return instence;
	}
	LoginManager& getLoginManager() {
		return _manager;
	}
	RoomManger& getRoomsManager() {
		return _roomsManager;
	}
	StatisticManager& getStatManager() {
		return _statManager;
	}
	GameManger& getGameManger(){
		return _gameManager;
	}
	IRequestHandler* getFirstRequsetHandler(const Buffer& buffer)const;
private:
	RequsetFactory();
	LoginManager _manager;
	RoomManger _roomsManager;
	StatisticManager _statManager;
	GameManger _gameManager;
};

