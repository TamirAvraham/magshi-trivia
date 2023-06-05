namespace ServicesForTrivia
{
    public struct RoomData
    {
        private List<User>? users;
        public bool isActive;
        public readonly string name;
        public readonly int id;
        public readonly int numOfQuestions;
        public readonly int TimePerQuestion;
        public readonly int maxNumOfPlayers;

        public RoomData(List<User>? users, bool isActive, string name, int id, int timeForQuestion, int numOfQuestions ,int maxNumOfPlayers) : this()
        {
            Users = users!;
            this.isActive = isActive;
            this.name = name;
            this.id = id;
            
            this.numOfQuestions = numOfQuestions;
            TimePerQuestion = timeForQuestion;
            this.maxNumOfPlayers = maxNumOfPlayers;
            
        }

        public List<User> Users { get => (users??=new List<User>()); set => users = value; }

        
    }
}
