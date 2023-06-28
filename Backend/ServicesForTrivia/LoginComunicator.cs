using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static class LoginComunicator
    {
        const byte logoutCode = 27;

        public static User SignUp(string username, string password, string email)
        {
            var requestDataAsJson=new JsonObject();

            requestDataAsJson["username"] = username;
            requestDataAsJson["password"] = password;
            requestDataAsJson["email"] = email;

            var responseDataAsString=requestDataAsJson.ToString();
            var buffer=new Buffer(
                data: Encoding.ASCII.GetBytes(responseDataAsString),
                sizeOfData: (ushort)responseDataAsString.Length,
                status: (byte)RequsetsStatues.SignUp
            );

            Communicator.Instance.SendBuffer(ref buffer);
            buffer = Communicator.Instance.ReadBuffer();

            if (buffer.Status == ((byte)ResponceStatus.Error))
            {
                throw new Exception("sign up error");
            }


            return new User(username);
        }
        public static User Login(string username, string password)
        {
            JsonObject requestDataAsJson = new JsonObject();

            requestDataAsJson.Add("username", username);
            requestDataAsJson.Add("password", password);

            var requestDataAsString = requestDataAsJson.ToString();

            var buffer = new Buffer(
                data: Encoding.ASCII.GetBytes(requestDataAsString),
                sizeOfData: (ushort)requestDataAsString.Length,
                status: (byte)RequsetsStatues.Login
            );
            
            Communicator.Instance.SendBuffer( ref buffer );
            buffer=Communicator.Instance.ReadBuffer();

            if (buffer.Status==((byte)ResponceStatus.Error))
            {
                throw new Exception($"login error:{Encoding.ASCII.GetString(buffer.Data)}");
            }


            return new User(username);
        }
        public static bool Logout(string username)
        {
            var req = new { username };
            string reqAsString = JsonSerializer.Serialize(req);
            byte[] bytes = Encoding.ASCII.GetBytes(reqAsString);

            var buffer = new Buffer(bytes, ((ushort)bytes.Length), logoutCode);
            Communicator.Instance.SendBuffer(ref buffer);

            buffer = Communicator.Instance.ReadBuffer();

            return buffer.Status == ((byte)ResponceStatus.Ok);

        }
    }
}
