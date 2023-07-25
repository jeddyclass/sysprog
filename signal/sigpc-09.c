#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;

// Signal handler for SIGALRM
void handle_alarm(int sig)
{
    alarm_fired = 1;
}

int main()
{
    pid_t child_pid;

    printf("Alarm application starting\n");

    // Create a child process using fork
    child_pid = fork();
    switch (child_pid)
    {
    case -1:
        // Fork failed
        perror("fork failed");
        exit(1);
    case 0:
        // Child process
        // Sleep for 5 seconds and then send SIGALRM signal to the parent
        printf("\tchile process ok, sleep 5 seconds.\n");
        sleep(5);
        printf("\tsend siganl:SIGALRM.\n");
        kill(getppid(), SIGALRM);
        exit(0);
    }

    // Parent process
    printf("Waiting for alarm to go off\n");

    // Set up the signal handler for SIGALRM
    (void)signal(SIGALRM, handle_alarm);

    // Wait for the SIGALRM signal to be caught
    pause();

    // If SIGALRM signal was caught, print "Ding!"
    if (alarm_fired)
        printf("Ding!!!!! Alarm alarmd!!!!\n");

    printf("Done, got SIGALRM.\n");
    exit(0);
}

