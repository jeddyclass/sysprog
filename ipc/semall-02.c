#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <errno.h>

#define NSEMS 3
#define SEM_KEY 1234

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    int semid;
    union semun arg;
    unsigned short values[NSEMS] = {2, 4, 6}; // Initial semaphore values

    // Create the semaphore set
    semid = semget(SEM_KEY, NSEMS, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Set the semaphore values
    arg.array = values;
    if (semctl(semid, 0, SETALL, arg) == -1) {
        perror("semctl SETALL");
        exit(EXIT_FAILURE);
    }

    printf("Semaphore values have been set to: %d, %d, %d\n", values[0], values[1], values[2]);

    // Get the current semaphore values
    for (int i = 0; i < NSEMS; i++) {
        values[i] = 0; // Reset values to read into
    }

    arg.array = values;
    if (semctl(semid, 0, GETALL, arg) == -1) {
        perror("semctl GETALL");
        exit(EXIT_FAILURE);
    }

    printf("Current semaphore values are: %d, %d, %d\n", values[0], values[1], values[2]);

    // Remove the semaphore set
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID");
        exit(EXIT_FAILURE);
    }

    return 0;
}

