#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t sigusr1_count = 0;

void sigusr1_handler(int signum) {
    sigusr1_count++;
    printf("Received SIGUSR1 signal (%d times)\n", sigusr1_count);
}

int main() {
    signal(SIGUSR1, sigusr1_handler);

    // Print the current process ID (PID)
    printf("Current PID: %d\n", getpid());

    while (1) {
        sleep(1);
        if (sigusr1_count >= 5) {
            printf("Exiting the program after receiving SIGUSR1 five times\n");
            break;
        }
    }

    return 0;
}

