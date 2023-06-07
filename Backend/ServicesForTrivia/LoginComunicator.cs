using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Nodes;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    public static class LoginComunicator
    {
        public static User SignUp(string username, string password, string email)
        {
            var requestDataAsJson=new JsonObject();

            requestDataAsJson["username"] = username;
            requestDataAsJson["password"] = password;
            requestDataAsJson["email"] = email;

            var responseDataAsString=requestDataAsJson.ToString();
            var buffer=new Buffer(
                data: Encoding.UTF8.GetBytes(responseDataAsString),
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
                data: Encoding.UTF8.GetBytes(requestDataAsString),
                sizeOfData: (ushort)requestDataAsString.Length,
                status: (byte)RequsetsStatues.Login
            );
            
            Communicator.Instance.SendBuffer( ref buffer );
            buffer=Communicator.Instance.ReadBuffer();

            if (buffer.Status==((byte)ResponceStatus.Error))
            {
                throw new Exception($"login error:{buffer.Data}");
            }


            return new User(username);
        }
        
    }
}
