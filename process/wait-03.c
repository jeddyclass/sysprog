#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    for (int i = 0; i < 3; i++) {
        pid = fork();

        if (pid == -1) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // This code block runs in the child process
            printf("Child process %d - My PID: %d\n", i + 1, getpid());
            sleep(3); // Simulate some work in the child process
            exit(0); // Terminate the child process
        }
    }

    // This code block runs in the parent process
    printf("Parent process - My PID: %d\n", getpid());

    // Wait for all child processes to finish
    printf("Parent process is waiting for child processes to finish...\n");
    for (int i = 0; i < 3; i++) {
        pid_t child_pid = wait(&status);
        printf("Child process %d with PID %d has finished\n", i + 1, child_pid);
    }

    return 0;
}

