using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public struct RoomState
    {
        [JsonPropertyName("status")]
        public int Status { get; set; }

        [JsonPropertyName("players")]
        public List<string> Players { get; set; }

        [JsonPropertyName("answerCount")]
        public int AnswerCount { get; set; }

        [JsonPropertyName("answerTimeOut")]
        public string AnswerTimeOut { get; set; }
    }

    public static class RoomMemberComunicator
    {
        /*
         * constexpr char ADMIN_CHAR = '4';
           constexpr unsigned char CloseRoomCode = 41;
           constexpr unsigned char StartRoomCode = 42;

           constexpr char MEMBER_CHAR = '5';
           constexpr unsigned char getRoomStateCode = 51;
           constexpr unsigned char LeaveRoomCode = 52;
        */

        const byte getRoomState = 51;
        const byte LeaveRoomCode = 52;

        public static bool LeaveRoom(int roomId, string username)
        {
            var req = new { roomId, username };

            string reqAsString = JsonSerializer.Serialize(req);
            byte[] bytes = Encoding.UTF8.GetBytes(reqAsString);

            Buffer buffer = new(bytes, ((ushort)bytes.Length), LeaveRoomCode);

            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();

            return buffer.Status == ((byte)ResponceStatus.Ok);
        }


        public static RoomState GetRoomState(int roomid)
        {
            var reqAsObject = new { roomid };
            var reqAsString = JsonSerializer.Serialize(reqAsObject);
            var reqAsByteArray = Encoding.ASCII.GetBytes(reqAsString);

            var buffer = new Buffer(reqAsByteArray, ((ushort)reqAsByteArray.Length), getRoomState);
            var comm = Communicator.Instance;
            comm.SendBuffer(ref buffer);

            buffer = comm.ReadBuffer();
            var res = Encoding.ASCII.GetString(buffer.Data);

            if (buffer.Status == ((byte)ResponceStatus.Error))
            {
                throw new Exception(res);
            }

            var ret = JsonSerializer.Deserialize<RoomState>(res);
            return ret;
        }
    }
    public static class AdminRoomComunicator
    {
        /*
         * constexpr char ADMIN_CHAR = '4';
           constexpr unsigned char CloseRoomCode = 41;
           constexpr unsigned char StartRoomCode = 42;
         */

        const byte CloseRoomCode = 41;
        const byte StartRoomCode = 42;

        //this will be added in v4.0.0

        public static int StartRoom(User user, int roomId)
        {
            var req = new { username = user.username, roomId = roomId };
            string reqAsString = JsonSerializer.Serialize(req);
            var reqAsBytes = Encoding.ASCII.GetBytes(reqAsString);

            var buffer = new Buffer(reqAsBytes, ((ushort)reqAsBytes.Length), StartRoomCode);
            Communicator.Instance.SendBuffer(ref buffer);

            buffer = Communicator.Instance.ReadBuffer();
            string data = Encoding.ASCII.GetString(buffer.Data);
            return JsonDocument.Parse(data).RootElement.GetProperty("id").GetInt32();
        }
        public static bool CloseRoom(string username,int roomId)
        {
            var req = new { roomId, username };

            string reqAsString = JsonSerializer.Serialize(req);
            byte[] bytes = Encoding.UTF8.GetBytes(reqAsString);

            Buffer buffer = new(bytes, ((ushort)bytes.Length), CloseRoomCode);

            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();

            return buffer.Status == ((byte)ResponceStatus.Ok);
        }
    }
}
