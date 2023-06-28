#include "JsonRequestPacketDeserializer.h"
#include "JsonObject.h"
#define getIntFromJson(param_name) (unsigned int)json[#param_name].integer_value()
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    auto username = reqAsJson["username"];
    std::string password = reqAsJson["password"].string_value();
    auto ret = LoginRequest{ 
        ._username = username.string_value(),
        ._password = password
    };
    delete[] buffer.data;
    ret.id = buffer.status;
    return ret;
}

SignUpRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    auto ret = SignUpRequest{
        ._username = reqAsJson["username"].string_value(),
        ._password = reqAsJson["password"].string_value(),
        ._email = reqAsJson["email"].string_value()
    };
    delete[] buffer.data;
    ret.id = buffer.status;
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
    std::string username = reqAsJson["username"].string_value();
    RoomData roomData = RoomDatafromJson(reqAsJson);
    auto ret = CreateRoomRequest{ .username =username , .roomData = roomData };
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

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    unsigned int roomId = static_cast<unsigned int>(reqAsJson["roomId"].integer_value());
    std::string username = reqAsJson["username"].string_value();
    auto ret = JoinRoomRequest{ .roomId = roomId, .username = username };
    ret.id = joinRoomCode;
    return ret;
}

LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(const Buffer& buffer)
{
    http::json::JsonObject reqAsJson(buffer.data);
    auto ret = LogoutRequest{ .username = reqAsJson["username"].string_value() };
    ret.id = buffer.status;
    return ret;
}

GetTopPlayersRequest JsonRequestPacketDeserializer::deserializeGetTopPlayersRequest(const Buffer& buffer)
{
    GetTopPlayersRequest ret;
    ret.id = buffer.status;
    return ret;
}

GetPlayerStatisticsRequest JsonRequestPacketDeserializer::deserializeGetPlayerStatisticsRequest(const Buffer& buffer)
{
    auto json = http::json::JsonObject(buffer.data);
    GetPlayerStatisticsRequest ret;
    ret.id = buffer.status;
    ret.playerUsername = json["username"].string_value();
    return ret;
}

CloseRoomRequest JsonRequestPacketDeserializer::deserializeCloseRoomRequest(const Buffer& buffer)
{
    auto json = http::json::JsonObject(buffer.data);
    CloseRoomRequest ret;
    ret.id = buffer.status;
    ret.roomId = json["roomId"].integer_value();
    ret.username = json["username"].string_value();
    return ret;
}

LeaveRoomRequest JsonRequestPacketDeserializer::deserializeLeaveRoomRequest(const Buffer& buffer)
{
    LeaveRoomRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.roomId = json["roomId"].integer_value();
    ret.username = json["username"].string_value();
    return ret;
}

StartRoomRequest JsonRequestPacketDeserializer::deserializeStartRoomRequest(const Buffer& buffer)
{
   StartRoomRequest ret;
   auto json = http::json::JsonObject(buffer.data);
   ret.id = buffer.status;
   ret.roomId = json["roomId"].integer_value();
   ret.username = json["username"].string_value();
   return ret;
}

GetRoomStateRequest JsonRequestPacketDeserializer::deserializeGetRoomStateRequest(const Buffer& buffer)
{
   GetRoomStateRequest ret;
   auto json = http::json::JsonObject(buffer.data);
   ret.id = buffer.status;
   ret.roomId = json["roomid"].integer_value();
   return ret;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const Buffer& buffer)
{
    SubmitAnswerRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.answer = json["answer"].string_value();
    ret.question = json["question"].string_value();
    ret.username = json["username"].string_value();
    ret.gameId = json["gameId"].integer_value();
    ret.timeToAnswer = json["timeToAnswer"].integer_value();
    return ret;
}

GetAnswersRequest JsonRequestPacketDeserializer::deserializeGetAnswersRequest(const Buffer& buffer)
{
    GetAnswersRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.gameId = json["gameId"].integer_value();
    ret.question = json["question"].string_value();
    return ret;
}

GetQuestionRequest JsonRequestPacketDeserializer::deserializeGetQuestionRequest(const Buffer& buffer)
{
    GetQuestionRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.gameId = json["gameId"].integer_value();
    ret.username = json["username"].string_value();
    return ret;
}

GetCorrectAnswerRequest JsonRequestPacketDeserializer::deserializeGetCorrectAnswerRequest(const Buffer& buffer)
{
    GetCorrectAnswerRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.gameId = json["gameId"].integer_value();
    ret.question = json["question"].string_value();
    return ret;
}

GetUserPointsRequest JsonRequestPacketDeserializer::deserializeGetUserPointsRequest(const Buffer& buffer)
{
     GetUserPointsRequest ret;
     auto json = http::json::JsonObject(buffer.data);
     ret.id = buffer.status;
     ret.gameId = json["gameId"].integer_value();
     ret.username = json["username"].string_value();
     return ret;
}

GetGameResultsRequest JsonRequestPacketDeserializer::deserializeGetGameResultsRequest(const Buffer& buffer)
{
    GetGameResultsRequest ret;
    auto json = http::json::JsonObject(buffer.data);
    ret.id = buffer.status;
    ret.gameId = json["gameId"].integer_value();
    ret.username = json["username"].string_value();
    return ret;
}


RoomData JsonRequestPacketDeserializer::RoomDatafromJson(const http::json::JsonObject& json)
{
    return RoomData{
        .id = getIntFromJson(id),
        .name = json["Name"].string_value(),
        .maxPlayers = getIntFromJson(MaxPlayers),
        .numOfQustions = getIntFromJson(NumOfQuestions),
        .TimePerQuestion = getIntFromJson(TimePerQuestion),
        .isActive = 0
    };
}
