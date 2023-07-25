#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Include this header for the sleep function


sem_t semaphoreA, semaphoreB;

void* threadA(void* arg) {
    sem_wait(&semaphoreA);
    printf("Thread A acquired semaphore A\n");

    // Sleep to simulate some work
    sleep(2);

    printf("Thread A is waiting for semaphore B...\n");
    sem_wait(&semaphoreB);
    printf("Thread A acquired semaphore B\n");

    sem_post(&semaphoreA);
    sem_post(&semaphoreB);

    pthread_exit(NULL);
}

void* threadB(void* arg) {
    sem_wait(&semaphoreB);
    printf("Thread B acquired semaphore B\n");

    // Sleep to simulate some work
    sleep(2);

    printf("Thread B is waiting for semaphore A...\n");
    sem_wait(&semaphoreA);
    printf("Thread B acquired semaphore A\n");

    sem_post(&semaphoreA);
    sem_post(&semaphoreB);

    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the semaphores
    sem_init(&semaphoreA, 0, 1);
    sem_init(&semaphoreB, 0, 1);

    // Create two threads
    pthread_create(&thread1, NULL, threadA, NULL);
    pthread_create(&thread2, NULL, threadB, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy the semaphores
    sem_destroy(&semaphoreA);
    sem_destroy(&semaphoreB);

    return 0;
}

