#pragma once
#include "requests.h"
#define JsonRequestPacketDeserializerMethod(struct_name) static struct_name##Request deserialize ##struct_name##Request (const Buffer& buffer);
class JsonRequestPacketDeserializer
{
	
public:
	static LoginRequest deserializeLoginRequest(Buffer buffer);
	static SignUpRequest deserializeSignUpRequest(Buffer buffer);
	static GetRoomPlayersRequest deserializeGetRoomRequest(const Buffer& buffer);
	static RemoveRoomRequest deserializeRemoveRoomRequest(const Buffer& buffer);
	static GetRoomsRequest deserializeRoomsRequest(const Buffer& buffer);
	static CreateRoomRequest deserializeCreateRoomsRequset(const Buffer& buffer);
	static GetRoomStatusRequest deserializeGetRoomStatusRequest(const Buffer& buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buffer);

	static GetTopPlayersRequest deserializeGetTopPlayersRequest(const Buffer& buffer);
	static GetPlayerStatisticsRequest deserializeGetPlayerStatisticsRequest(const Buffer& buffer);

	static CloseRoomRequest deserializeCloseRoomRequest(const Buffer& buffer);
	static LeaveRoomRequest deserializeLeaveRoomRequest(const Buffer& buffer);
	static StartRoomRequest deserializeStartRoomRequest(const Buffer& buffer);
	static GetRoomStateRequest deserializeGetRoomStateRequest(const Buffer& buffer);

	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const Buffer& buffer);
	static GetAnswersRequest deserializeGetAnswersRequest(const Buffer& buffer);
	static GetQuestionRequest deserializeGetQuestionRequest(const Buffer& buffer);
	static GetCorrectAnswerRequest deserializeGetCorrectAnswerRequest(const Buffer& buffer);
	static GetUserPointsRequest deserializeGetUserPointsRequest(const Buffer& buffer);
	static GetGameResultsRequest deserializeGetGameResultsRequest(const Buffer& buffer);

private:
	static RoomData RoomDatafromJson(const http::json::JsonObject& json);
};

