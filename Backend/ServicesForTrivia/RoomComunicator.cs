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
        //public static RoomData GetRoom(int roomId)
        //{

        //}
        public static void RefreshRoomStatus(ref RoomData data)
        {
            Buffer buffer=new Buffer(data:new byte[0],0,25);
            Communicator.Instance.SendBuffer(buffer);
            buffer = Communicator.Instance.ReadBuffer();
            JsonDocument document = JsonDocument.Parse(Encoding.ASCII.GetString(buffer.Data));
            data.isActive = document.RootElement.GetProperty("status").GetBoolean();

        }
        public static List<RoomData> GetRooms()
        {
            Buffer buffer = Communicator.Instance.ReadBuffer();
            return JsonSerializer.Deserialize<List<RoomData>>(Encoding.ASCII.GetString(buffer.Data))!;
        }
        
        private static RoomData GetRoomFromBuffer(ref Buffer roomBuffer)
        {
            return JsonSerializer.Deserialize<RoomData>(Encoding.ASCII.GetString(roomBuffer.Data));
        }
    }
}
