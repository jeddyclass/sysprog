#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#define WORK_SIZE 1024

// Global variables
char work_area[WORK_SIZE]; // Shared work area between main thread and worker thread
sem_t bin_sem; // Semaphore to synchronize communication between threads

// Worker thread function
void* worker_thread(void* arg) {
    sem_wait(&bin_sem); // Wait for the semaphore to be signaled by the main thread

    while(strncmp("end", work_area, 3) != 0) {
        // Process the input received from the main thread
        printf("Worker Thread: You input %zu characters\n", strlen(work_area) - 1);

        sem_post(&bin_sem); // Release the semaphore to allow the main thread to input new data
        sem_wait(&bin_sem); // Wait for the semaphore to be signaled again by the main thread
    }

    pthread_exit(NULL);
}

int main() {
    int res;
    pthread_t worker_thread_id;
    void* thread_result;

    // Initialize the semaphore with an initial value of 0 (not signaled)
    res = sem_init(&bin_sem, 0, 0);
    if (res != 0) {
        perror("Semaphore initialization failed");
        exit(EXIT_FAILURE);
    }

    // Create the worker thread
    res = pthread_create(&worker_thread_id, NULL, worker_thread, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Input some text. Enter 'end' to finish\n");
    while (strncmp("end", work_area, 3) != 0) {
        if (strncmp(work_area, "FAST", 4) == 0) {
            sem_post(&bin_sem); // Signal the semaphore to wake up the worker thread
            strcpy(work_area, "Wheeee..."); // Modify the work_area while worker thread processes previous input
        } else {
            fgets(work_area, WORK_SIZE, stdin); // Get input from the user
        }
        sem_post(&bin_sem); // Signal the semaphore to wake up the worker thread again
    }

    printf("\nWaiting for worker thread to finish...\n");
    res = pthread_join(worker_thread_id, &thread_result); // Wait for the worker thread to finish
    if (res != 0) {
        perror("Worker thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Worker thread joined\n");

    // Destroy the semaphore
    sem_destroy(&bin_sem);

    exit(EXIT_SUCCESS);
}

