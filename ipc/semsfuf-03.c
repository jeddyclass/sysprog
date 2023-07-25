#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <string.h>

#define SEM_NAME "/my_semaphore"
#define FILE_NAME "shared_file.txt"
#define NUM_PROCESSES 3
#define NUM_UPDATES 5

int main() {
    sem_t *semaphore;
    int i, fd;
    char buffer[50];

    // Create or open the semaphore
    semaphore = sem_open(SEM_NAME, O_CREAT, 0644, 1);
    if (semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Open the shared file
    fd = open(FILE_NAME, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Initialize the file with initial content
    sprintf(buffer, "Initial content\n");
    write(fd, buffer, strlen(buffer));

    // Fork multiple processes
    for (i = 0; i < NUM_PROCESSES; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            for (int j = 0; j < NUM_UPDATES; j++) {
                // Acquire the semaphore
                sem_wait(semaphore);

                // Read the current content of the file
                lseek(fd, 0, SEEK_SET);
                ssize_t read_bytes = read(fd, buffer, sizeof(buffer));
                buffer[read_bytes] = '\0';

                // Update the content
                sprintf(buffer, "Process %d updated the file\n", getpid());
                lseek(fd, 0, SEEK_SET);
                write(fd, buffer, strlen(buffer));

                // Release the semaphore
                sem_post(semaphore);

                // Sleep for some time to simulate other activities
                sleep(rand() % 2);
            }

            close(fd);
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all child processes to finish
    for (i = 0; i < NUM_PROCESSES; i++) {
        wait(NULL);
    }

    // Close and remove the semaphore
    sem_close(semaphore);
    sem_unlink(SEM_NAME);

    printf("All processes have finished updating the file.\n");

    return 0;
}

