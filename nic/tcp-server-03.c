#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sockfd, new_sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
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
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("Listen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("TCP server is listening on port %d...\n", SERVER_PORT);

    // Accept incoming connections and process messages
    while (1) {
        new_sockfd = accept(sockfd, (struct sockaddr*)&client_addr, &client_len);
        if (new_sockfd < 0) {
            perror("Accept failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        printf("Accepted a new connection from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        while (1) {
            int bytes_received = recv(new_sockfd, buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received < 0) {
                perror("Recv failed");
                close(new_sockfd);
                close(sockfd);
                exit(EXIT_FAILURE);
            } else if (bytes_received == 0) {
                // Client closed the connection
                printf("Connection closed by client\n");
                break;
            }

            buffer[bytes_received] = '\0';
            printf("Received message from client: %s\n", buffer);

            // Echo the message back to the client
            send(new_sockfd, buffer, bytes_received, 0);
        }

        close(new_sockfd);
    }

    close(sockfd);
    return 0;
}

