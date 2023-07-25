#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
    char *message;
    int n;
    int exit_code;

    printf("fork program starting\n");

    // Create a new process using fork()
    pid = fork();
    switch (pid) 
    {
    case -1:
        exit(1);
    case 0:
        // This code executes in the child process
        message = "This is the child";
        n = 5;
        exit_code = 404;
        // exit(exit_code % 256);
        break;
    default:
        // This code executes in the parent process
        message = "This is the parent";
        n = 3;
        exit_code = 0;
        break;
    }

    // Both child and parent process execute this loop
    for (; n > 0; n--) {
        puts(message);
        sleep(1);
    }

    /* This section of the program waits for the child process to finish. */
    if (pid) {
        int stat_val;
        pid_t child_pid;

        printf("Parent process is waiting for the child process to finish...\n");
        
        // Wait for the child process to finish and store its PID and exit status
        child_pid = wait(&stat_val);

        printf("Child has finished: PID = %d\n", child_pid);

        // Check if the child exited normally or abnormally and print the exit status
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else
            printf("Child terminated abnormally\n");
    }

    // Both child and parent process exit here
    exit(exit_code);
}

