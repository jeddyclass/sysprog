#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int num) {
    write(STDOUT_FILENO, "Received SIGINT or SIGTERM. Exiting...\n", 39);
    exit(EXIT_SUCCESS);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Handle SIGINT (Ctrl+C)
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction(SIGINT) error");
        return EXIT_FAILURE;
    }

    // Handle SIGTERM
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("sigaction(SIGTERM) error");
        return EXIT_FAILURE;
    }

    while (1) {
        printf("inf loop ..., pid:[%d]\n", getpid());
        sleep(1);
    }
    return 0;
}


