using System.Text.Json;
using System.Text.Json.Serialization;

namespace ServicesForTrivia
{
    public struct StatisticsData
    {
        [JsonPropertyName("user")]
        public string Username { get; set; }

        [JsonPropertyName("total_games")]
        public int TotalGames { get; set; }

        [JsonPropertyName("total_answers")]
        public int TotalAnswers { get; set; }

        [JsonPropertyName("correct_answers")]
        public int CorrectAnswers { get; set; }

        [JsonPropertyName("total_seconds")]
        public int TotalSeconds { get; set; }
    }

}