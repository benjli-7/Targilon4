from socket import socket, AF_INET, SOCK_DGRAM
# The socket will use UDP connection

s = socket(AF_INET, SOCK_DGRAM)
# creation of a UDP socket  (socket = a "hub" for data transfer)

dst_ip = '127.0.0.1'
# The IP address of the server the client will send data to
dst_port = 12345
# The port on the server machine the data will be sent to

s.sendto(b'If youll be my bodyguard, I can be your long lost pal', (dst_ip,dst_port))
# The client sends the message "hello" to the server

data, sender_info = s.recvfrom(2048)
# The client receives a 2048-byte sized message from the server
# As well as details about the server
print(data.decode('utf-8'))
# The received data is printed to the screen...
print(sender_info)
# with information about the sender

s.close()
# The client is shut down
