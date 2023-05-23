#pragma once
#include "LoginManager.h"
#include "RoomsManger.h"
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
	IRequestHandler* getFirstRequsetHandler(const Buffer& buffer)const;
private:
	RequsetFactory();
	LoginManager _manager;
	RoomManger _roomsManager;
	//u will need to add a db connection here
};

