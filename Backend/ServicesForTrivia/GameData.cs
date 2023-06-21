using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public struct GameData
    {
        [JsonPropertyName("user")]
        public string Username { get; set; }

        [JsonPropertyName("points")]
        public string Points { get; set; }

        [JsonPropertyName("correct_answers")]
        public int CorrectAnswers { get; set; }

        [JsonPropertyName("total_seconds")]
        public int TotalSeconds { get; set; }
    }
}
