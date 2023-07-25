#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Create TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set up the server address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(SERVER_PORT);

    // Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Enter a message to send to the server (or 'q' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove the newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "q") == 0) {
            break;
        }

        // Send the message to the server
        send(sockfd, buffer, strlen(buffer), 0);

        // Receive a response from the server
        int bytes_received = recv(sockfd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("Recv failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        } else if (bytes_received == 0) {
            // Server closed the connection
            printf("Connection closed by server\n");
            break;
        }

        buffer[bytes_received] = '\0';
        printf("Received from server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}

