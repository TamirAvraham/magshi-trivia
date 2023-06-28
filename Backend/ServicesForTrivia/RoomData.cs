using System.Text.Json.Serialization;

namespace ServicesForTrivia
{
    public struct RoomData
    {
        /*
        http::json::JsonObject toJson()const {
		http::json::JsonObject object;
		object.insert({ "id",{std::to_string(id)} });
		object.insert({ "name",{name} });
		object.insert({ "maxPlayers",{std::to_string(maxPlayers)} });
		object.insert({ "numOfQustions",{ std::to_string(numOfQustions) } });
		object.insert({ "TimePerQuestion",{ std::to_string(TimePerQuestion) } });
		object.insert({ "isActive",{isActive ? "true" : "false"} });
		return object;
	}
         */
        private uint isActive;
        private  string name;
        public  int id;
        private  int numOfQuestions;
        private  int timePerQuestion;
        private int maxNumOfPlayers;
        
         [JsonPropertyName("TimePerQuestion")]
         public int TimePerQuestion => this.numOfQuestions;

        [JsonPropertyName("id")]
        public int Id => this.id;

        [JsonPropertyName("isActive")]
        public uint IsActive { get => isActive; set => isActive=value; }

        [JsonPropertyName("maxPlayers")]
        public int MaxPlayers => this.maxNumOfPlayers;

        [JsonPropertyName("name")]
        public string Name => this.name;

        [JsonPropertyName("numOfQustions")]
        public int NumOfQuestions => this.numOfQuestions;
        
        public RoomData( uint isActive, string name, int id, int timeForQuestion, int numOfQuestions ,int maxNumOfPlayers) : this()
        {
            
            this.isActive = isActive;
            this.name = name;
            this.id = id;
            
            this.numOfQuestions = numOfQuestions;
            timePerQuestion = timeForQuestion;
            this.maxNumOfPlayers = maxNumOfPlayers;
            
        }
        

        
    }
}
