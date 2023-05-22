#include "JsonRequestPacketDeserializer.h"
#include "JsonObject.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    auto username = reqAsJson["username"];
    std::string password = reqAsJson["password"].string_value();
    auto ret = LoginRequest{ 
        ._username = username.string_value(),
        ._password = password
    };
    delete[] buffer.data; //clean the buffer data since it is in the heap
    return ret;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(Buffer buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
        auto ret = SignUpRequest{
        ._username = reqAsJson["username"].string_value(),
        ._password = reqAsJson["password"].string_value(),
        ._email = reqAsJson["email"].string_value()
        };

    delete[] buffer.data; //clean the buffer data since it is in the heap
    return ret;
}

GetRoomRequest JsonRequestPacketDeserializer::deserializeGetRoomRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    return GetRoomRequest{ .roomId = (unsigned int)reqAsJson["roomId"].integer_value() };
}

RemoveRoomRequest JsonRequestPacketDeserializer::deserializeRemoveRoomRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    return RemoveRoomRequest{ .roomId = (unsigned int)reqAsJson["roomId"].integer_value() };
}

RoomsRequest JsonRequestPacketDeserializer::deserializeRoomsRequest(const Buffer& buffer)
{
    return RoomsRequest();
}

CreateRoomsRequset JsonRequestPacketDeserializer::deserializeCreateRoomsRequset(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    auto roomData = RoomDatafromJson(reqAsJson);
    return CreateRoomsRequset{ 
        .userId = reqAsJson["userId"].integer_value(),
        .roomData=roomData 
    };
}

GetRoomStatusRequest JsonRequestPacketDeserializer::deserializeGetRoomStatusRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    return GetRoomStatusRequest{ .roomId = (unsigned int)reqAsJson["roomId"].integer_value() };
}

RoomData JsonRequestPacketDeserializer::RoomDatafromJson(const http::json::JsonObject& json)
{
    return RoomData{
        .id = getIntFromJson(id),
        .name = json["name"].string_value(),
        .maxPlayers = getIntFromJson(maxPlayers),
        .numOfQustions = getIntFromJson(numOfQustions),
        .TimePerQuestion = getIntFromJson(TimePerQuestion),
        .isActive = false
    };
}
