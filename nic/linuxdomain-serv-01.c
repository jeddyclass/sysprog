#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/my_socket"

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    char buffer[1024];
    ssize_t num_bytes;

    // Create a socket
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the socket to a path
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH); // Remove the file if it already exists
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is waiting for connections...\n");

    while (1) {
        // Accept incoming connection
        socklen_t client_addr_len = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        printf("Client connected!\n");

        // Read data from the client
        while ((num_bytes = read(client_socket, buffer, sizeof(buffer))) > 0) {
            buffer[num_bytes] = '\0';
            printf("Received from client: %s", buffer);
        }

        if (num_bytes == -1) {
            perror("read");
        }

        close(client_socket);
        printf("Client disconnected.\n");
    }

    close(server_socket);
    unlink(SOCKET_PATH); // Clean up the socket file
    return 0;
}

