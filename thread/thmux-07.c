#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 4

int counter = 0; // Global counter
pthread_mutex_t mutex; // Mutex to protect the counter

void* thread_function(void* arg) {
    int i;
    int* increment = (int*)arg;
    
    for (i = 0; i < 100000; i++) {
        // Lock the mutex before accessing the shared counter
        pthread_mutex_lock(&mutex);

        // Critical section: Update the counter
        counter += *increment;

        // Unlock the mutex after finishing the critical section
        pthread_mutex_unlock(&mutex);
    }
    printf("\tcalled, counter: %d\n", counter);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int i;

    // Initialize the mutex attributes and create the mutex
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutex_init(&mutex, &mutex_attr);

    // Create multiple threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the mutex
    pthread_mutexattr_destroy(&mutex_attr);
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}

