#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


volatile sig_atomic_t sigusr1_received = 0;
volatile sig_atomic_t sigusr2_received = 0;

void sigusr1_handler(int signum) {
    sigusr1_received = 1;
}

void sigusr2_handler(int signum) {
    sigusr2_received = 1;
}

int main() {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        // Child Process
        signal(SIGUSR1, sigusr1_handler);
        while (1) {
            if (sigusr1_received) {
                printf("Child: Received SIGUSR1 signal\n");
                sigusr1_received = 0;
            }
        }
    } else if (pid > 0) {
        // Parent Process
        signal(SIGUSR2, sigusr2_handler);
        sleep(1);
        kill(pid, SIGUSR1); // Send SIGUSR1 signal to the child
        sleep(2);
        kill(pid, SIGUSR2); // Send SIGUSR2 signal to the child
        wait(NULL); // Wait for the child to terminate
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}


