#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    printf("Before fork(): This is the original program\n");

    // Fork a new process
    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // This code executes in the child process

        // Replace the child process with the 'ls' command
        // The 'ls' command lists the files in the current directory
        execl("/bin/ls", "ls", "-l", NULL);

        // The following code will only execute if execl() fails
        perror("execl failed");
        return 1;
    } else {
        // This code executes in the parent process

        // Wait for the child process to finish
        int status;
        waitpid(pid, &status, 0);

        printf("After fork() and execl(): Back to the original program\n");
    }

    return 0;
}

