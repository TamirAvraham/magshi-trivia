namespace ServicesForTrivia
{
    public struct User
    {
        public readonly string username;
        public bool isAdmin=false;
        public User(string username)
        {
            this.username = username;
        }
    }
}
