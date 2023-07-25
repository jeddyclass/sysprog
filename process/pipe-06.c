#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include this header for wait function

int main() {
    int pipe_fd[2];
    pid_t pid;
    char message[] = "Hello, child!";

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[1]); // Close the write end of the pipe in the child process

        char buffer[100];
        read(pipe_fd[0], buffer, sizeof(buffer));
        sleep(1);
        printf("\tChild received: %s\n", buffer);

        close(pipe_fd[0]); // Close the read end of the pipe in the child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe in the parent process

        write(pipe_fd[1], message, sizeof(message));
        printf("Parent sent: %s\n", message);

        close(pipe_fd[1]); // Close the write end of the pipe in the parent process
        sleep(2);
        wait(NULL); // Wait for the child to finish

        printf("Parent: Child process has finished.\n");
    }

    return 0;
}

