#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>

#define SHM_SIZE 1024
#define SHM_KEY 1234

void *write_to_shared_memory(void *arg);
void *read_from_shared_memory(void *arg);

int main() {
    int shmid;
    char *shmaddr;

    // Create the shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach the shared memory segment to the process
    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Create two threads to read and write from/to shared memory
    pthread_t write_thread, read_thread;
    pthread_create(&write_thread, NULL, write_to_shared_memory, (void *)shmaddr);
    pthread_create(&read_thread, NULL, read_from_shared_memory, (void *)shmaddr);

    // Wait for the threads to finish
    pthread_join(write_thread, NULL);
    pthread_join(read_thread, NULL);

    // Detach the shared memory segment from the process
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

void *write_to_shared_memory(void *arg) {
    char *shmaddr = (char *)arg;
    const char *message = "Hello from the write thread!";
    strcpy(shmaddr, message);
    printf("Write thread: Message written to shared memory: %s\n", message);
    pthread_exit(NULL);
}

void *read_from_shared_memory(void *arg) {
    char *shmaddr = (char *)arg;
    sleep(1); // Give the write thread some time to write to shared memory
    printf("Read thread: Message read from shared memory: %s\n", shmaddr);
    pthread_exit(NULL);
}

