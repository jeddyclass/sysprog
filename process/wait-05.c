#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define NPROCS 2    // number of child processes to create

int main()
{
    pid_t child_pid;
    int i;
    int child_status; // child's exit value

    // Create the child processes
    fprintf(stdout, "Parent: Creating %u child processes\n", NPROCS);
    for (i = 0; i < NPROCS; i++)
    {
        child_pid = fork();

        if (child_pid == -1)
        {
            fprintf(stderr, "fork() failed, errno=%d\n", errno);
            return 1;
        }
        else if (child_pid == 0)
        {
            // This is the child process
            fprintf(stdout, "Child: I'm a new born child, my pid=%u\n", getpid());
            fprintf(stdout, "Child: my parent is pid=%u\n", getppid());
            sleep(2);
            return 0;
        }
    }

    // This is the parent

    // Send a signal to the last child
    kill(child_pid, SIGKILL);

    // Wait for all child processes to exit
    for (i = 0; i < NPROCS; i++)
    {
        child_pid = wait(&child_status);
        fprintf(stdout, "Child %u has terminated\n", child_pid);

        // See if the child terminated normally.
        // WIFEXITED(stat) evaluates to non-zero if a child has terminated normally,
        // whether it returned zero or non-zero.
        if (WIFEXITED(child_status))
        {
            fprintf(stdout, "Child %u has terminated normally\n", child_pid);
            if (WEXITSTATUS(child_status))
                fprintf(stdout, "The lowest byte of exit value for child %u is %d\n",
                        child_pid, WEXITSTATUS(child_status));
            else
                fprintf(stdout, "Child %d has returned a value of 0\n", child_pid);
        }

        // See if the child terminated due to a signal
        if (WIFSIGNALED(child_status) != 0)
        {
            // Child terminated due to a signal
            fprintf(stdout, "Child %d terminated due to a signal\n", child_pid);
            fprintf(stdout, "Child %d terminated due to getting signal %d\n",
                    child_pid, WTERMSIG(child_status));
        }
    }

    return 0;
}

