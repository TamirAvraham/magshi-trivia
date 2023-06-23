using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static class QuestionCommunicator
    {
        const byte getQuestion = 61;
        const byte getAnswers = 62;
        const byte getCorrectAnswer = 63;
        public static QuestionData GetQuestion(string username)
        {
            var req = new { username = username };
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
            var req = new { question = question};
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
            return JsonSerializer.Deserialize<String>(data);
        }
    }
}
