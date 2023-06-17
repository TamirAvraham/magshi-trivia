using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static class StatisticsCommunicator
    {
        const byte getPlayerStatistic = 31;
        const byte getTopPlayers = 32;

        public static StatisticsData GetPlayerStatistic(string username)
        {
            var req = new { username = username };
            var usernameasbytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(req));
            var buffer = new Buffer(usernameasbytes, ((ushort)usernameasbytes.Length), getPlayerStatistic);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            var ret = JsonSerializer.Deserialize<StatisticsData>(data);
            return ret;

        }
        public static List<(string,int)> getTopFive()
        {
            var buffer = new Buffer(Array.Empty<byte>(), 0, getTopPlayers);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);


            List<(string, int)> dataList = new List<(string, int)>();

            // Parse the JSON string into a JsonDocument
            using JsonDocument document = JsonDocument.Parse(data)!;

            // Get the root element of the document (assuming it's an array)
            JsonElement root = document.RootElement;

            // Iterate over the elements in the array
            foreach (JsonElement element in root.EnumerateArray())
            {
                // Extract the "user" and "points" properties
                string user = element.GetProperty("user").GetString()!;
                int points = element.GetProperty("points").GetInt32()!;
                dataList.Add((user, points));
            }

            return dataList;
        }
    }
}