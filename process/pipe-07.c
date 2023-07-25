#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int parent_to_child[2]; // Pipe from parent to child
    int child_to_parent[2]; // Pipe from child to parent
    pid_t pid;
    char message_to_child[] = "Hello, child!";
    char message_to_parent[] = "Hello, parent!";

    if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
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
        close(parent_to_child[1]); // Close the write end of the parent-to-child pipe in the child process
        close(child_to_parent[0]); // Close the read end of the child-to-parent pipe in the child process

        sleep(1); // Pause to observe the flow

        char buffer[100];
        read(parent_to_child[0], buffer, sizeof(buffer));
        printf("Child received from parent: %s\n", buffer);

        // Send a message to the parent
        write(child_to_parent[1], message_to_parent, sizeof(message_to_parent));

        close(parent_to_child[0]); // Close the read end of the parent-to-child pipe in the child process
        close(child_to_parent[1]); // Close the write end of the child-to-parent pipe in the child process
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(parent_to_child[0]); // Close the read end of the parent-to-child pipe in the parent process
        close(child_to_parent[1]); // Close the write end of the child-to-parent pipe in the parent process

        // Send a message to the child
        write(parent_to_child[1], message_to_child, sizeof(message_to_child));

        sleep(1); // Pause to observe the flow

        char buffer[100];
        read(child_to_parent[0], buffer, sizeof(buffer));
        printf("Parent received from child: %s\n", buffer);

        close(parent_to_child[1]); // Close the write end of the parent-to-child pipe in the parent process
        close(child_to_parent[0]); // Close the read end of the child-to-parent pipe in the parent process

        sleep(1); // Pause to observe the flow
        wait(NULL); // Wait for the child to finish

        printf("Parent: Child process has finished.\n");
    }

    return 0;
}

