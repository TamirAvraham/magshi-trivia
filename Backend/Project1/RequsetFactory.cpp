#include "RequsetFactory.h"
#include <iostream>
#include "SignupRequestHandler.h"
#include "LoginRequestHandler.h"
#include "RoomsHandlers.h"
#include "RoomMemberHandler.h"

IRequestHandler* RequsetFactory::getFirstRequsetHandler(const Buffer& buffer) const
{
    switch (buffer.status)
    {
    case LOGIN:
        return new LoginRequestHandler();
    case SIGNUP:
        return new SignupRequestHandler();
    case getRoomsCode:
        return new RoomsHandler();
    case getRoomStateCode:
        return new RoomMemberHandler();
    default:
        //The user shouldn't know that the format is wrong, only the server should
        std::cout << "Got a message with invalid format!\nMessage Status: " << buffer.status << "\nMessage data:\n" << buffer.data;
        break;
    }
    return nullptr;
}

RequsetFactory::RequsetFactory()
{
}

