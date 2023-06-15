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

        // public static StatisticsData getPlayerStatistic(string username)
        // {
        //     var usernameAsBytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(username));
        //     var buffer = new Buffer(usernameAsBytes, ((ushort)usernameAsBytes.Length), getPlayerStatistic);
        //     Communicator.Instance.SendBuffer(ref buffer);
        //     buffer = Communicator.Instance.ReadBuffer();
        //     var data = Encoding.ASCII.GetString(buffer.Data);
        //     StatisticsData ret = new StatisticsData();
        //     ret.Username = data.
            
        // }
    }
}