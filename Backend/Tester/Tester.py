
import socket
import Buffer
# define the host and port to connect to
HOST = 'localhost'
PORT = 12

print("Enter 1 for signup, anything else for login")
x = int(input())

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to the host and port
s.connect((HOST, PORT))


if x == 1:
    signup_json_data="""
    {
        "username": "test user name",
        "password": 1234,
        "email" : "testEmail@gmail.com"
    }
    """
    signup_status=76
    signup_buffer=Buffer.Buffer(signup_status,len(signup_json_data),signup_json_data)
    s.send(signup_buffer.to_bytes())
    data = s.recv(1024)
    print('got data')
    buff=Buffer.Buffer.from_bytes(data)
    # print the data to the screen
    print(f"status:{buff.status} size of data: {buff.sizeOfData} {buff.data}")
else:
    login_json_data="""
    {
        "username": "test user name",
        "password": 1234
    }
    """
    login_status=76
    login_buffer=Buffer.Buffer(login_status,len(login_json_data),login_json_data)
    s.send(login_buffer.to_bytes())
    data = s.recv(1024)
    print('got data')
    buff=Buffer.Buffer.from_bytes(data)
    # print the data to the screen
    print(f"status:{buff.status} size of data: {buff.sizeOfData} {buff.data}")

# close the socket connection
s.close()
