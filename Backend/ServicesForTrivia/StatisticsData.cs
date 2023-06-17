using System.Text.Json;

namespace ServicesForTrivia
{
    public struct StatisticsData
    {
        private string username;
        private int total_games;
        private int total_answers;
        private int correct_answers;
        private int total_seconds;
        
        public StatisticsData(string username, int total_answers, int correct_answers, int total_seconds, int total_games)
        {
            this.username = username;
            this.total_answers = total_answers;
            this.correct_answers = correct_answers;
            this.total_seconds = total_seconds;
            this.total_games = total_games;
        }
        
        
        public int Total_answers { get => total_answers; set => total_answers = value; }
        public int Total_seconds { get => total_seconds; set => total_seconds = value; }
        public string Username { get => username; set => username = value; }
        public int Total_games { get => total_games; set => total_games = value; }
        public int Correct_answers { get => correct_answers; set => correct_answers = value; }
    }

    public struct GameData
    {
        private string username;
        private int points;

        public GameData(string username, int points)
        {
            this.username = username;
            this.points = points;
        }

        public string Username { get => username; set => username = value; }
        public int Points { get => points; set => points = value; }
    }
}