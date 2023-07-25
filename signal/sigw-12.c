#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

void* threadFunction(void* arg) {
    printf("called threadFunction, then sleep 2 sec...\n");
    sleep(2); // Sleep for 2 seconds before sending the signal to the main thread
    printf("Sending SIGUSR1 signal to the main thread...\n");
    pthread_kill((pthread_t)arg, SIGUSR1); // Send SIGUSR1 signal to the main thread
    printf("Sending SIGUSR1 done...\n");
    return NULL;
}

int main() {
    sigset_t signalSet;
    int sig;
    pthread_t thread;

    // Block SIGUSR1 signal in the main thread
//    sigemptyset(&signalSet);
//    sigaddset(&signalSet, SIGUSR1);
//    pthread_sigmask(SIG_BLOCK, &signalSet, NULL);

    // Create a new thread
    if (pthread_create(&thread, NULL, threadFunction, (void*)pthread_self()) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    printf("Main thread waiting for SIGUSR1 signal...\n");

    // Wait for SIGUSR1 signal using sigwait
    if (sigwait(&signalSet, &sig) != 0) {
        perror("sigwait");
        exit(EXIT_FAILURE);
    }

    printf("Main thread received SIGUSR1 signal. Exiting...\n");

    return 0;
}

