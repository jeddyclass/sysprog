//send message to chhild thread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
char message[50] = "";

void *thread_function(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("Thread is waiting for the message...\n");
    while (message[0] == '\0') {
        pthread_cond_wait(&cond, &mutex);
    }
    printf("Thread received the message: %s\n", message);
    message[0] = '\0';
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main() {
    int result;
    pthread_t thread;

    result = pthread_create(&thread, NULL, thread_function, NULL);
    if (result != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Sending a message to the thread...\n");
    pthread_mutex_lock(&mutex);
    strcpy(message, "Hello from the main thread!");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    result = pthread_join(thread, NULL);
    if (result != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Main thread is exiting.\n");
    exit(EXIT_SUCCESS);
}

