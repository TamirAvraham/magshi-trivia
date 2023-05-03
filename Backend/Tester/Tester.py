
import socket

# define the host and port to connect to
HOST = 'localhost'
PORT = 12

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to the host and port
s.connect((HOST, PORT))

# receive data from the socket
data = s.recv(1024)

# print the data to the screen
print(data.decode())

# close the socket connection
s.close()
