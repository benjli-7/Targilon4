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

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // UDP socket created, designated for IPV4
    if (sock < 0) {
        // If the socket creation function returned a negative number, it means the socket's creation failed
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    // Address the server receives data from

    memset(&sin, 0, sizeof(sin));
    // All the struct's properties and contents are set to 0 to avoid data corruption

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    // IP address reformatted from string to fit sockaddr's structure

    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        // The server is "bound" to the socket the data will be received from
        // and to the address specified in sockaddr (in this implementation - any address)
        // If the returned int is negative, it means the binding failed
        perror("error binding to socket");
    }

    struct sockaddr_in from;
    // Address the server receives data from
    unsigned int from_len = sizeof(struct sockaddr_in);
    // The length of message received
    char buffer[4096];
    // Specification of "data chunk" size received by the server
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    // Data is received by the server (to the socket specified in sock, and address specified in sockaddr)
    if (bytes < 0) {
        // If the number returned is negative, it means the transfer failed
        perror("error reading from socket");
    }

    cout << "The client sent: " << buffer << endl;

    char buffer_tosend[] = "Join the dark side, we have cookies"
    // CHANGE: The message being sent back to the client
    int sent_bytes = sendto(sock, buffer_tosend, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    // Data is sent to the client
    if (sent_bytes < 0) {
        // If the int returned is negative, it means that the transfer failed
        perror("The message could not be resent to client");
    }

    close(sock);
    // The client socket is closed; no more data can be received until the program will be restarted

    return 0;
}