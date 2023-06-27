using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static partial class QuestionCommunicator
    {

        const byte getQuestion = 61;
        const byte getAnswers = 62;
        const byte getCorrectAnswer = 63;
        const byte submitAnswer = 65;
        const byte getGameResults = 66;


        public static QuestionData GetQuestion(string username, int gameId)
        {
            var req = new { username = username, gameId };
            var usernameasbytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(req));
            var buffer = new Buffer(usernameasbytes, ((ushort)usernameasbytes.Length), getQuestion);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            var ret = JsonSerializer.Deserialize<QuestionData>(data);
            return ret;
            
        }
        public static List<String> GetAnswers(string question)
        {
            var req = new { question = question };
            var questionAsBytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(req));
            var buffer = new Buffer(questionAsBytes, ((ushort)questionAsBytes.Length), getAnswers);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            var ret = JsonSerializer.Deserialize<QuestionData>(data);
            return ret.AllAnswers;
        }

        public static String GetCorrectAnswer(string question)
        {
            var req = new { question = question };
            var questionAsBytes = Encoding.ASCII.GetBytes(JsonSerializer.Serialize(req));
            var buffer = new Buffer(questionAsBytes, ((ushort)questionAsBytes.Length), getCorrectAnswer);
            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();
            var data = Encoding.ASCII.GetString(buffer.Data);
            return JsonSerializer.Deserialize<String>(data)!;
        }
        public static bool SubmitAnswer(string question, int gameId, string username, int timeToAnswer, string answer)
        {
            var req = new { question = question, gameId = gameId, username, timeToAnswer, answer };

            string reqAsString = JsonSerializer.Serialize(req);
            var reqAsBytes = Encoding.ASCII.GetBytes(reqAsString);

            var buffer = new Buffer(reqAsBytes, ((ushort)reqAsBytes.Length), submitAnswer);

            Communicator.Instance.SendBuffer(ref buffer);

            buffer = Communicator.Instance.ReadBuffer();

            string data = Encoding.ASCII.GetString(buffer.Data);
            return JsonDocument.Parse(data).RootElement.GetProperty("correctAnswer").GetBoolean();
        }
        public static List<GameResult> GetGameResults(int gameId,string username)
        {
            var req = new { gameId = gameId, username };
            string reqAsString = JsonSerializer.Serialize(req);
            var reqAsBytes = Encoding.ASCII.GetBytes(reqAsString);

            var buffer = new Buffer(reqAsBytes, ((ushort)reqAsBytes.Length), getGameResults);

            Communicator.Instance.SendBuffer(ref buffer);

            buffer = Communicator.Instance.ReadBuffer();

            string data = Encoding.ASCII.GetString(buffer.Data);
            var ret = JsonDocument.Parse(data).RootElement.GetProperty("results").Deserialize<List<GameResult>>()!;
            return ret;
        }
    }
}
