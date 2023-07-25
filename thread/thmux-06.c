#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
char message[50] = "";

void *client_thread(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("Client thread is waiting for the message...\n");
    while (message[0] == '\0') {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Client thread received the message: %s\n", message);
    //message[0] = '\0';
    strcpy(message, "Hello from the client thread!");
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    int result;
    pthread_t thread;

    result = pthread_create(&thread, NULL, client_thread, NULL);
    if (result != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Main process is waiting for a message from the client thread...\n");
    sleep(1); // To ensure client thread starts first
    pthread_mutex_lock(&mutex);
    strcpy(message, "Hello from the server thread!");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    result = pthread_join(thread, NULL);
    if (result != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Main process received the client thread's message: %s\n", message);

    printf("Main process is exiting.\n");
    exit(EXIT_SUCCESS);
}

