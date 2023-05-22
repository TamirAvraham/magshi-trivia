#pragma once
#include <string>
#include <chrono>
#include "RoomsManger.h"
constexpr unsigned char LOGIN = 'L';
constexpr unsigned char SIGNUP = 'S';
constexpr unsigned char OK = 'O';
constexpr unsigned char Error = 'E';

struct Buffer
{
	unsigned char status;
	unsigned int sizeOfData;
	char* data;
	std::chrono::steady_clock::time_point time = std::chrono::high_resolution_clock::now();
};
struct Request
{
	unsigned char id;
};
struct LoginRequest:Request
{
	std::string _username;
	std::string _password;
};
struct SignUpRequest:Request
{
	std::string _username;
	std::string _password;
	std::string _email;
};
struct GetRoomRequest:Request
{
	unsigned int roomId;
};
struct GetRoomStatusRequest :Request
{
	unsigned int roomId;
};
struct RemoveRoomRequest :Request
{
	unsigned int roomId;
};
struct RoomsRequest :Request
{
};

struct CreateRoomsRequset:Request
{
	int userId;
	RoomData roomData;
};