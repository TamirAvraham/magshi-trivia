#pragma once
#include <string>
#include <chrono>
#include "RoomsManger.h"
#define request(name) struct name##Request:Request{};
constexpr unsigned char LOGIN = 'L';
constexpr unsigned char SIGNUP = 'S';

constexpr unsigned char OK = 'O';
constexpr unsigned char Error = 'E';

constexpr char ROOM_CHAR = '2';
constexpr unsigned char getRoomCode = 21;
constexpr unsigned char getRoomsCode = 22;
constexpr unsigned char deleteRoomCode = 23;
constexpr unsigned char createRoomCode = 24;
constexpr unsigned char getRoomStatus = 25;
constexpr unsigned char joinRoomCode = 26;

constexpr char STATISTICS_CHAR = '3';
constexpr unsigned char getPlayerStatistics = 31;
constexpr unsigned char getTopPlayers = 32;

constexpr char ADMIN_CHAR = '4';
constexpr unsigned char CloseRoomCode = 41;
constexpr unsigned char StartRoomCode = 42;

constexpr char MEMBER_CHAR = '5';
constexpr unsigned char getRoomStateCode = 51;
constexpr unsigned char LeaveRoomCode = 52;

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
struct GetRoomPlayersRequest:Request
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
struct GetRoomsRequest :Request
{
};

struct CreateRoomRequest:Request
{
	std::string username;
	RoomData roomData;
};
struct JoinRoomRequest : Request
{
	unsigned int roomId;
	std::string username;
};

struct GetTopPlayersRequest:Request
{

};
struct GetPlayerStatisticsRequest:Request
{
	std::string playerUsername;
};
struct CloseRoomRequest :Request {
	int roomId;
	std::string username;
};
struct StartRoomRequest :Request {
	int roomId;
	std::string username;
};
struct LeaveRoomRequest :Request {
	int roomId;
	std::string username;
};
//get room state
struct GetRoomStateRequest :Request {
	int roomId;
};