using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace ServicesForTrivia
{
    public static class RoomComunicator
    {
        const byte getRoomStatus = 25;
        const byte getRoom = 21;
        const byte getRooms = 22;
        const byte joinRoom = 26;
        const byte createRoom = 24;
        static JsonSerializerOptions options = new JsonSerializerOptions { PropertyNameCaseInsensitive = true };

        public static RoomData? GetRoom(int roomId)
        {
            List<RoomData> temp = GetRooms(Communicator.Instance);
            for (int i = 0; i < temp.Count; i++)
            {
                if (roomId == temp[i].id)
                {
                    return temp[i];
                }
            }
            return null;    // If no room with such id exists
        }
        
        public static void RefreshRoomStatus(ref RoomData data)
        {
            Buffer buffer=new Buffer(data:new byte[0],0,getRoomStatus);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            JsonDocument document = JsonDocument.Parse(Encoding.ASCII.GetString(buffer.Data));
            data.IsActive = document.RootElement.GetProperty("status").GetBoolean();

        }
        
        public static List<RoomData> GetRooms(Communicator communicator)
        {
            Buffer buffer = new Buffer(data: new byte[0], 0, getRooms);
            communicator.SendBuffer(ref buffer);
            buffer = communicator.ReadBuffer();
            if (buffer.Status==((byte)ResponceStatus.Error)||buffer.Status==123)
            {
                return new List<RoomData>();
            }
            var data = Encoding.ASCII.GetString(buffer.Data);
            var document = JsonDocument.Parse(data);
            var roomsProperty = document.RootElement.GetProperty("rooms");
            var rooms = new List<RoomData>();

            foreach (var roomElement in roomsProperty.EnumerateArray())
            {
                var id = roomElement.GetProperty("id").GetInt32();
                var name = roomElement.GetProperty("name").GetString();
                var maxPlayers = roomElement.GetProperty("maxPlayers").GetInt32();
                var numOfQuestions = roomElement.GetProperty("numOfQustions").GetInt32();
                var timePerQuestion = roomElement.GetProperty("TimePerQuestion").GetInt32();
                var isActive = roomElement.GetProperty("isActive").GetBoolean();

                var roomData = new RoomData(isActive, name, id, timePerQuestion, numOfQuestions, maxPlayers);
                rooms.Add(roomData);
            }

            return rooms;

        }
        public static bool JoinRoom(string Username, int RoomId)
        {
            var request = new { username = Username, roomId = RoomId };
            var requestAsBytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(request));
            Buffer buffer = new Buffer(data: requestAsBytes, ((ushort)requestAsBytes.Length), joinRoom);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            return (buffer.Status == ((byte)ResponceStatus.Ok));

        }
        public static bool CreateRoom(RoomData roomData,User user)
        {
            var combinedObject = new
            {
                user.username,
                roomData.IsActive,
                roomData.Name,
                roomData.id,
                roomData.NumOfQuestions,
                roomData.TimePerQuestion,
                roomData.MaxPlayers
            };

            string s = JsonSerializer.Serialize(combinedObject);
            byte[] store= Encoding.ASCII.GetBytes(s);
            var buffer = new Buffer(store, ((ushort)store.Length), createRoom);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            return buffer.Status == ((byte)ResponceStatus.Ok);
        }
        private static RoomData GetRoomFromBuffer(ref Buffer roomBuffer)
        {
            return JsonSerializer.Deserialize<RoomData>(Encoding.ASCII.GetString(roomBuffer.Data));
        }
    }
}
