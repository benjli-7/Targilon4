import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# creation of a TCP socket  (socket = a "hub" for data transfer)

server_ip = ''
# Empty string because the server is set to accept data from any IP address

server_port = 12345
# The port from which the server will receive the data

server.bind((server_ip, server_port))
# The socket is set to receive data coming into its port 12345
# from any address

server.listen(5)
# The server is set to allow up to 5 simultaneous connection requests
# the sixth and the next ones will be denied

while True:
    client_socket, client_address = server.accept()
    # The server waits for a message from a client and then receives
    # the socket and address the message is sent from

    print('Connection from: ', client_address)
    # The IP address of the client is printed

    data = client_socket.recv(1024)
    # 1024 - size of "data chunk" taken at each iteration

    while not data.decode('utf-8') == '':
        # While part of the message was not printed yet -
        print('Received: ', data.decode('utf-8'))
        # The current chunk is printed
        client_socket.send(data.upper())
        # The data is resent to the client, now in upper case

        data = client_socket.recv(1024)
        # 1024byte sized data chunk is received from the client

    print('Client disconnected')
    # When all the message was read, the server will disconnect from the current client
    client_socket.close()
    # The connection with the current client is closed