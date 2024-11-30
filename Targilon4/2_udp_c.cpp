#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;
    // The IP address and socket of the server machine

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    // UDP socket created, designated for IPV4

    if (sock < 0) {
        // If the socket creation function returned a negative number, it means the socket's creation failed
        perror("error creating socket");
    }

    struct sockaddr_in sin;
    // Address the client sends data to
    memset(&sin, 0, sizeof(sin));
    // All the struct's properties and contents are set to 0 to avoid data corruption
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    // IP address reformatted from string to fit sockaddr's structure
    sin.sin_port = htons(port_no);

    char data[] = "Join the dark side, we have cookies";
    // CHANGE: The message being sent to the server
    int data_len = sizeof(data);

    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    // Data is sent to server (to the socket specified in sock, and address specified in sockaddr)
    // The number of transfered bytes is returned to sent_bytes
    if (sent_bytes < 0) {
        // If the number returned is negative, it means the transfer failed
        perror("error writing to socket");
    }

    struct sockaddr_in from;
    // Address the client receives data from
    unsigned int from_len = sizeof(struct sockaddr_in);
    // The size of received data
    char buffer[4096];
    // Specification of "data chunk" size received by the client
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    // Data is received from the server (to the socket specified in sock, and address specified in sockaddr)
    if (bytes < 0) {
        // If the number returned is negative, it means the transfer failed
        perror("error reading from socket");
    }

    cout << "The server sent: " << buffer << endl;

    close(sock);
    // The client socket is closed; no more data can be received until the program will be restarted

    return 0;
}