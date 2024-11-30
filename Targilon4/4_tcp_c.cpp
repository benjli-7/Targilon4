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


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    // TCP socket created, designated for IPV4

    struct sockaddr_in sin;
    // Address the client sends data to
    memset(&sin, 0, sizeof(sin));
    // All the struct's properties and contents are set to 0 to avoid data corruption
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    // IP address reformatted from string to fit sockaddr's structure
    sin.sin_port = htons(port_no);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        // The client tries to connect to the server, if the returned int is negative
        // It means that the connection failed
        perror("error connecting to server");
    }

    char data_addr[] = "You are on this council, but we do not grant you the rank of master.";
    // CHANGE: The message sent (from "Call me Al" by Paul Simon)
    // The message that will be sent to the server
    int data_len = strlen(data_addr);
    // The length of the sent message
    int sent_bytes = send(sock, data_addr, data_len, 0);
    // The number of bytes successfully sent to the server

    if (sent_bytes < 0) {
    // If the number is negative, it means the data transfer failed
    // error
    }

    char buffer[4096];
    // The array data will be received into
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    // The number of bytes successfully received from the server
    if (read_bytes == 0) {
    // If there is no more data to receive...
    cout << "Connection is closed, no more data to receive"
    // CHANGE: message is printed when the connection is closed
    }
    else if (read_bytes < 0) {
    // error
    }
    else {
        cout << buffer;
        // The received data chunk is printed
    }

    close(sock);

    return 0;
}