using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ServicesForTrivia
{
    internal class Buffer
    {
        private byte[] data;
        private uint sizeOfData;
        
        private byte status;

        public Buffer(byte[] data, uint sizeOfData, byte status)
        {
            Data = data;
            SizeOfData = sizeOfData;
            Status = status;
        }

        public byte[] Data { get => data; set => data = value; }
        public uint SizeOfData { get => sizeOfData; set => sizeOfData = value; }
        public byte Status { get => status; set => status = value; }

    }
}
