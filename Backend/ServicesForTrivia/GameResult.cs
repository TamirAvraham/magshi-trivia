using System.Text.Json.Serialization;

namespace ServicesForTrivia
{
    public static partial class QuestionCommunicator
    {
        public class GameResult
        {
            [JsonPropertyName("username")]
            public string Username { get; set; }

            [JsonPropertyName("correctAnswerCount")]
            public int CorrectAnswerCount { get; set; }

            [JsonPropertyName("averageAnswerTime")]
            public int AvgAnswerTime { get; set; }

            [JsonPropertyName("points")]
            public int Points { get; set; }

            public override string? ToString()
            {
                return $"{Username} : {Points} , {AvgAnswerTime}s , {CorrectAnswerCount}";
            }
        }
    }
}
