
import socket
import Buffer
# define the host and port to connect to
HOST = 'localhost'
PORT = 12

print("Enter 0 for error, 1 for signup, anything else for login")
x = int(input())

# create a socket object
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect to the host and port
s.connect((HOST, PORT))

#"username": "test user name",
if x == 0:
    error_json_data="""
    {
        "password": "1234"
    }
    """
    error_status=83
    error_buffer=Buffer.Buffer(error_status,len(error_json_data),error_json_data)
    s.send(error_buffer.to_bytes())
    data = s.recv(1024)
    print('got data')
    buff=Buffer.Buffer.from_bytes(data)
    # print the data to the screen
    print(f"status:{buff.status} size of data: {buff.sizeOfData} {buff.data}")
elif x == 1:
    print("Enter username:")
    username = input()
    print("Enter password:")
    password = input()
    print("Enter email:")
    email = input()
    
    signup_json_data = '\n{\n\t"username": "' + username + '"\n\t"password": "' + password + '"\n\t"email": "' + email + '"\n}\n'

    signup_status=83
    signup_buffer=Buffer.Buffer(signup_status,len(signup_json_data),signup_json_data)
    s.send(signup_buffer.to_bytes())
    data = s.recv(1024)
    print('got data')
    buff=Buffer.Buffer.from_bytes(data)
    # print the data to the screen
    print(f"status:{buff.status} size of data: {buff.sizeOfData} {buff.data}")
else:
    print("Enter username:")
    username = input()
    print("Enter password:")
    password = input()

    login_json_data = '\n{\n\t"username": "' + username + '"\n\t"password": "' + password + '"\n}\n'
    print(login_json_data)

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
