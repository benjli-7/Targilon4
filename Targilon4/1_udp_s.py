from socket import socket, AF_INET, SOCK_DGRAM
# The socket will use UDP connection

s = socket(AF_INET, SOCK_DGRAM)
# creation of a UDP socket  (socket = a "hub" for data transfer)

src_ip = ''
# Empty string because the server is set to accept data from any IP address
src_port = 12345
# The port from which the server will receive the data
s.bind((src_ip, src_port))
# The socket is set to receive data coming into its port 12345
# from any address

while True:
# Because the server is expected to run forever (unless the program is closed)
    data, sender_info = s.recvfrom(2048)
# 2048 - size of "data chunk" taken at each iteration
    print(data.decode('utf-8'))
# We expect the received data to be text encoded in UTF-8
# The received data is printed to the screen...
    print(sender_info)
# with information about the sender

    s.sendto(data.lower(), sender_info)
# CHANGE: The data is sent back to the sender lower-cased