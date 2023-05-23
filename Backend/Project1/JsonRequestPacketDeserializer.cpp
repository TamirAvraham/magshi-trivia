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

GetRoomPlayersRequest JsonRequestPacketDeserializer::deserializeGetRoomRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    unsigned int roomId = static_cast<unsigned int>(reqAsJson["roomId"].integer_value());
    auto ret = GetRoomPlayersRequest{ .roomId = roomId };
    ret.id = getRoomCode;
    return ret;
}

RemoveRoomRequest JsonRequestPacketDeserializer::deserializeRemoveRoomRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    unsigned int roomId = static_cast<unsigned int>(reqAsJson["roomId"].integer_value());
    auto ret = RemoveRoomRequest{ .roomId = roomId };
    ret.id = deleteRoomCode;
    return ret;
}

GetRoomsRequest JsonRequestPacketDeserializer::deserializeRoomsRequest(const Buffer& buffer)
{
    auto ret = GetRoomsRequest{};
    ret.id = getRoomsCode;
    return ret;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomsRequset(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    int userId = reqAsJson["userId"].integer_value();
    RoomData roomData = RoomDatafromJson(reqAsJson);
    auto ret = CreateRoomRequest{ .username = userId, .roomData = roomData };
    ret.id = createRoomCode;
    return ret;
}

GetRoomStatusRequest JsonRequestPacketDeserializer::deserializeGetRoomStatusRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    unsigned int roomId = static_cast<unsigned int>(reqAsJson["roomId"].integer_value());
    auto ret = GetRoomStatusRequest{ .roomId = roomId };
    ret.id = getRoomStatus;
    return ret;
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
