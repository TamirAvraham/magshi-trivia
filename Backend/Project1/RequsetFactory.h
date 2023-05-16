#pragma once
#include "LoginManager.h"
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
	IRequestHandler* getFirstRequsetHandler(const Buffer& buffer)const;
private:
	RequsetFactory();
	LoginManager _manager;
	//u will need to add a db connection here
};

