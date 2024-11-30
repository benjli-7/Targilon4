import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# creation of a TCP socket  (socket = a "hub" for data transfer)

dest_ip = '127.0.0.1'
# The IP address of the server the client will send data to

dest_port = 12345
# The port on the server machine the data will be sent to

s.connect((dest_ip, dest_port))
# Unlike the UDP server, here we start a steady connection
# (like a phone call)
# instead of one-time connection for sending specific data
# (like mail)

msg = input("Message to send: ")
# The user types a message to be sent to the server into the CLI
while not msg == 'quit':
    # While the client did not receive the message "quit" from the server...
    s.send(bytes(msg, 'utf-8'))
    # It will send it the message specified by the user
    data = s.recv(4096)
    # A data chunk will be received from the server
    print("Server sent: ", data.decode('utf-8'))
    # The message received from the server will be parsed as UTF-8 encoded text
    msg = input("Message to send: ")
    # A new message can be sent to the server

s.close()
# The connection will end when the user types "quit"