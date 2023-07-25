#include <stdio.h>
#include <unistd.h>

int main() {
    // Print the process ID (PID) before fork()
    printf("Before fork - My PID: %d\n", getpid());

    pid_t pid = fork(); // Create a child process

    if (pid == -1) {
        // Error occurred during fork()
        perror("Fork failed");
    } else if (pid == 0) {
        // This code block runs in the child process
        printf("Child process - My PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        // This code block runs in the parent process
        printf("Parent process - My PID: %d, Child PID: %d\n", getpid(), pid);
    }

    // Add sleep to observe the output easily
    sleep(5);

    return 0;
}

