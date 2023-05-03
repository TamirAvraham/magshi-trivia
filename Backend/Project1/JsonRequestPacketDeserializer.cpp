#include "JsonRequestPacketDeserializer.h"
#include "JsonObject.h"
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
