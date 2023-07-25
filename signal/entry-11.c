#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> // Added for malloc and free

// Define a key to store thread-specific data
pthread_key_t counter_key;

// A function to increment the counter
void incrementCounter() {
    int* counter_ptr = pthread_getspecific(counter_key);
    if (counter_ptr) {
        (*counter_ptr)++;
    }
}

// A cleanup function to release the thread-specific data
void cleanupCounter(void* counter_ptr) {
    if (counter_ptr) {
        free(counter_ptr);
    }
}

// Thread function
void* threadFunction(void* arg) {
    int* counter_ptr = (int*)malloc(sizeof(int));
    *counter_ptr = 0;

    // Set the thread-specific data for this thread
    pthread_setspecific(counter_key, counter_ptr);

    // Increment the counter
    for (int i = 0; i < 5; i++) {
        incrementCounter();
    }

    // Print the thread's counter value
    printf("Thread counter: %d\n", *counter_ptr);

    return NULL;
}

int main() {
    // Create a key to hold the thread-specific data
    pthread_key_create(&counter_key, cleanupCounter);

    // Create an array of threads
    pthread_t threads[5];

    // Create and run the threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the key
    pthread_key_delete(counter_key);

    return 0;
}

