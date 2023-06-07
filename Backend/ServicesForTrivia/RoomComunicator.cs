using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static class RoomComunicator
    {
        const byte getRoomStatus = 25;
        const byte getRoom = 21;
        const byte getRooms = 22;
        static JsonSerializerOptions options=new JsonSerializerOptions { PropertyNameCaseInsensitive=true };

        public static RoomData? GetRoom(int roomId)
        {
            List<RoomData> temp = GetRooms();
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
            data.isActive = document.RootElement.GetProperty("status").GetBoolean();

        }
        
        public static List<RoomData> GetRooms()
        {
            Buffer buffer = new Buffer(data: new byte[0], 0, getRooms);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            JsonDocument document = JsonDocument.Parse(data);
            return document.RootElement.GetProperty("rooms").Deserialize<List<RoomData>>(options)??new List<RoomData>();
        }

        private static RoomData GetRoomFromBuffer(ref Buffer roomBuffer)
        {
            return JsonSerializer.Deserialize<RoomData>(Encoding.ASCII.GetString(roomBuffer.Data));
        }
    }
}
