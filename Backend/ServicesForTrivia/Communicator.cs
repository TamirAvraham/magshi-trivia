using System.Net.Sockets;

namespace ServicesForTrivia
{
    class Communicator
    {
        const string ip = "127.0.0.1";
        const int port = 12;

        private  NetworkStream socket;
        private  TcpClient tcpClient;

        static Communicator? instance;
        public static Communicator Instance
        {
            get
            {
                instance ??= new Communicator();
                return instance;
            } 
        }

        private Communicator()
        {
            tcpClient = new TcpClient();
            tcpClient.Connect(ip, port);
            socket = tcpClient.GetStream();
        }

        public void SendBuffer(ref Buffer buffer)
        {
            int sizeOfBufferBytes = 5 + ((int)buffer.SizeOfData);
            var bytes = new byte[sizeOfBufferBytes];

            bytes[0] = buffer.Status;
            var sizeOfDataASBytes = BitConverter.GetBytes(buffer.SizeOfData);
            Array.Copy(sizeOfDataASBytes ,0, bytes, 1, 4);
            Array.Copy(buffer.Data, 0, bytes, 5, buffer.SizeOfData);

            socket.Write(bytes);
        }

        public Buffer ReadBuffer()
        {
            return Desirealizer.GetBufferFromSocket(socket);
        }
        ~Communicator()
        {
            tcpClient.Close();
        }
    }
}
