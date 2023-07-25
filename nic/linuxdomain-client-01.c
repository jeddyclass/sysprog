#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>

#define SOCKET_PATH "/tmp/my_socket"

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    char message[] = "Hello, server!";
    ssize_t num_bytes;

    // Create a socket
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    num_bytes = write(client_socket, message, strlen(message));
    if (num_bytes == -1) {
        perror("write");
    }

    close(client_socket);
    return 0;
}

