#include <stdio.h>
#include <pthread.h>

char *message = NULL;

void *client_thread(void *arg) {
    // Client thread sets the message
    message = "Hello from the client thread!";

    // Client thread exits, sending the message to the main process
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    // Create the client thread
    pthread_create(&tid, NULL, client_thread, NULL);

    // Main process waits for the client thread to finish and receive the message
    pthread_join(tid, NULL);

    // Print the message received from the client thread
    printf("Main process received the client thread's message: %s\n", message);

    printf("Main process is exiting.\n");
    return 0;
}

