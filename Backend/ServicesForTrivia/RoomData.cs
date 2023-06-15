namespace ServicesForTrivia
{
    public struct RoomData
    {
        
        public bool isActive;
        public readonly string name;
        public readonly int id;
        public readonly int numOfQuestions;
        public readonly int TimePerQuestion;
        public readonly int maxNumOfPlayers;

        public RoomData( bool isActive, string name, int id, int timeForQuestion, int numOfQuestions ,int maxNumOfPlayers) : this()
        {
            
            this.isActive = isActive;
            this.name = name;
            this.id = id;
            
            this.numOfQuestions = numOfQuestions;
            TimePerQuestion = timeForQuestion;
            this.maxNumOfPlayers = maxNumOfPlayers;
            
        }
        

        
    }
}
