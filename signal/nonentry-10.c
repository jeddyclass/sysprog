#include <stdio.h>
#include <pthread.h>

// A non-reentrant function that increments a global variable
void incrementCounter() {
    static int counter = 0; // Static variable to maintain state between calls
    counter++;
    printf("Counter value: %d\n", counter);
}

// Thread function that calls the non-reentrant function
void *threadFunction(void *arg) {
    for (int i = 0; i < 5; i++) {
        incrementCounter();
    }
    return NULL;
}

int main() {
    pthread_t threads[5];

    // Create multiple threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, threadFunction, NULL);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}

