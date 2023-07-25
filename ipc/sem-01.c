#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h> // Include this header for the wait() function


#define KEY_PATH "/tmp" // You can choose any valid directory for KEY_PATH
#define PROJ_ID 42       // Project ID for generating the key

#define NUM_SEMAPHORES 1 // Number of semaphores in the set

// Function to create and initialize the semaphore
int initializeSemaphore() {
    key_t key;
    int semid;

    // Generate the key using ftok()
    if ((key = ftok(KEY_PATH, PROJ_ID)) == -1) {
        perror("ftok");
        return -1;
    }

    // Create a new semaphore set with one semaphore
    if ((semid = semget(key, NUM_SEMAPHORES, IPC_CREAT | 0666)) == -1) {
        perror("semget");
        return -1;
    }

    // Initialize the semaphore with value 1 (unlocked)
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl");
        return -1;
    }

    return semid;
}

// Function to lock the semaphore
void semaphoreWait(int semid) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = -1;
    sem_op.sem_flg = SEM_UNDO;

    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

// Function to unlock the semaphore
void semaphoreSignal(int semid) {
    struct sembuf sem_op;
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = SEM_UNDO;

    if (semop(semid, &sem_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int semid = initializeSemaphore();

    printf("Main process: Semaphore created and initialized.\n");

    // Fork a child process
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("\tChild process: Waiting for the semaphore...\n");
        semaphoreWait(semid);

        // Critical section (shared resource access)
        printf("\t\tChild process: In the critical section.\n");
        sleep(5);
        printf("\t\tChild process: Exiting critical section.\n");

        // Release the semaphore
        semaphoreSignal(semid);

        // Child process finished
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        printf("\tParent process: Waiting for the semaphore...\n");
        semaphoreWait(semid);

        // Critical section (shared resource access)
        printf("\t\tParent process: In the critical section.\n");
        sleep(3);
        printf("\t\tParent process: Exiting critical section.\n");

        // Release the semaphore
        semaphoreSignal(semid);

        // Parent process finished
        wait(NULL); // Wait for the child process to finish
        printf("\nParent process: Child process has finished.\n");

        // Clean up: remove the semaphore set
        if (semctl(semid, 0, IPC_RMID) == -1) {
            perror("semctl");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}

