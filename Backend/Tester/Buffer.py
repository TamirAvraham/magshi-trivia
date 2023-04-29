class Buffer:
    def __init__(self, status: int, size_of_data: int, data: str):
        self.status = status
        self.sizeOfData = size_of_data
        self.data = data
        
    @staticmethod
    def from_bytes(buffer_bytes: bytes) -> 'Buffer':
        # Parse the status byte
        status = buffer_bytes[0]
        
        # Parse the size of data as a 4-byte integer
        size_of_data = int.from_bytes(buffer_bytes[1:5], byteorder='big')
        
        # Parse the data as a string
        data = buffer_bytes[5:].decode()
        
        return Buffer(status, size_of_data, data)
    
    def to_bytes(self) -> bytes:
        # Convert the status to a single byte
        status_byte = bytes([self.status])
        
        # Convert the size of data to a 4-byte integer
        size_of_data_bytes = self.sizeOfData.to_bytes(4, byteorder='little')
        
        # Convert the data to bytes
        data_bytes = self.data.encode()
        
        # Concatenate the bytes and return the result
        return status_byte + size_of_data_bytes + data_bytes



