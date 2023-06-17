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

        static JsonSerializerOptions options = new JsonSerializerOptions { PropertyNameCaseInsensitive = true };

        public static StatisticsData GetPlayerStatistic(string username)
        {
            var usernameAsBytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(username));
            var buffer = new Buffer(usernameAsBytes, ((ushort)usernameAsBytes.Length), getPlayerStatistic);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            JsonDocument document = JsonDocument.Parse(data);

            StatisticsData ret = new StatisticsData();
            ret.Username = document.RootElement.GetProperty("user").Deserialize<string>();
            ret.Total_games = int.Parse(document.RootElement.GetProperty("total_games").Deserialize<string>());
            ret.Total_answers = int.Parse(document.RootElement.GetProperty("total_answers").Deserialize<string>());
            ret.Total_seconds = int.Parse(document.RootElement.GetProperty("total_seconds").Deserialize<string>());
            ret.Correct_answers = int.Parse(document.RootElement.GetProperty("correct_answers").Deserialize<string>());
            return ret;
         }

        public static List<GameData> GetTopFive()
        {
            Buffer buffer = new Buffer(data: new byte[0], 0, getTopPlayers);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            JsonDocument document = JsonDocument.Parse(data);
            return document.RootElement.GetProperty("top_players").Deserialize<List<GameData>>(options) ?? new List<GameData>();
        }
    }
}