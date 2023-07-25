#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Key to access thread-specific data
pthread_key_t key;

// Function to be executed by each thread
void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // Allocate thread-specific data and associate it with the key
    int* thread_data = (int*)malloc(sizeof(int));
    *thread_data = thread_id;
    pthread_setspecific(key, thread_data);

    // Retrieve thread-specific data using pthread_getspecific()
    int* retrieved_data = (int*)pthread_getspecific(key);
    printf("Thread %d: Data retrieved = %d\n", thread_id, *retrieved_data);

    // Clean up allocated thread-specific data (optional)
    free(thread_data);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[3];
    int thread_args[3];
    int i;

    // Initialize the key for thread-specific data
    if (pthread_key_create(&key, NULL) != 0) {
        perror("pthread_key_create");
        exit(EXIT_FAILURE);
    }

    // Create multiple threads
    for (i = 0; i < 3; i++) {
        thread_args[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_args[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < 3; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    // Destroy the key for thread-specific data
    pthread_key_delete(key);

    return 0;
}

