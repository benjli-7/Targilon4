#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const int server_port = 5555;
    // The socket the server will receive data from

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    // TCP socket created, designated for IPV4

    if (sock < 0) {
        // If the socket creation function returned a negative number, it means the socket's creation failed
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    // Specified the address data can be received from

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    // The socket is set to accept any address data will be sent from
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        // If the bind creation function returned a negative number, it means that the binding failed
        perror("error binding socket");
    }

    if (listen(sock, 5) < 0) {
        // The TCP server can accept up to 5 connection requests simultaneously, the others will be denied
        perror("error listening to a socket");
    }

    struct sockaddr_in client_sin;
    // Specified the address of the socket (received at "sock")

    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock,  (struct sockaddr *) &client_sin,  &addr_len);
    // When a client sent a message to the server, the server will attempt to connect to the client

    if (client_sock < 0) {
        // If a negative number is returned, it means the socket could not accept the client's message
        perror("error accepting client");
    }

    char buffer[4096];
    // The array the message will be stored at
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    // The message from the client is put into "buffer"
    if (read_bytes == 0) {
        // If there is no message to receive...
    // connection is closed
    }
    else if (read_bytes < 0) {
        // If there was an error when the message was received...
    // error
    }
    else {
        cout << buffer;
        // The received message is printed to the user
    }

    int sent_bytes = send(client_sock, buffer, read_bytes, 0);
    // Attempt to resend the message to the client 

    if (sent_bytes < 0) {
        perror("The message could not be resent to client");
    }

    close(client_sock);
    close(sock);


    return 0;
}