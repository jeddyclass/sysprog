#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

// Function for thread 1
void* thread1_function(void* arg) {
    printf("Thread 1: Starting...\n");
    
    // Access a NULL pointer to cause a segmentation fault
    int* ptr = NULL;
    *ptr = 10;
    
    // This code will not be reached due to the segmentation fault
    printf("Thread 1: Exiting...\n");
    pthread_exit(NULL);
}

// Function for thread 2
void* thread2_function(void* arg) {
    printf("Thread 2: Starting...\n");
    
    // Sleep for a while to ensure thread 1 starts first
    sleep(2);
    
    // Send a SIGSEGV signal to itself to cause a segmentation fault
    pthread_kill(pthread_self(), SIGSEGV);
    
    // This code will not be reached due to the segmentation fault
    printf("Thread 2: Exiting...\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    
    // Create thread 1
    if (pthread_create(&thread1, NULL, thread1_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Create thread 2
    if (pthread_create(&thread2, NULL, thread2_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    
    // Wait for thread 1 to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    // Wait for thread 2 to finish
    if (pthread_join(thread2, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }
    
    // The code will not reach this point because one of the threads caused a segfault
    printf("Main thread: Exiting...\n");
    return 0;
}


