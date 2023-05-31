using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    internal static class Desirealizer
    {
        const int sizeOfHeader = 5;
        public static Buffer GetBufferFromSocket(NetworkStream networkStream)
        {
            var header = new byte[sizeOfHeader];
            networkStream.Read(header, 0, sizeOfHeader);

            var status = header[0];
            var sizeOfData = BitConverter.ToUInt32(header, 1);
            var data = new byte[sizeOfData];
            if (sizeOfData!=0)
            {
                networkStream.Read(data, 0, ((int)sizeOfData));

            }
            return new Buffer(data, sizeOfData, status);
        }
    }
}
