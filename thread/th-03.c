#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

// Function to be executed by the thread
void *thread_function(void *arg);

// Global variable to store the message
char global_message[] = "Hello World";

int main() {
    int result;
    pthread_t thread;
    void *thread_result;

    // Create a new thread and pass the global_message as the argument
    result = pthread_create(&thread, NULL, thread_function, (void *)global_message);
    if (result != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for thread to finish...\n");

    // Wait for the thread to finish
    // this is important, since wont do this, new thread could be no chance to run, and parent process is finish
    result = pthread_join(thread, &thread_result);
    if (result != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    printf("Thread joined, returned %s\n", (char *)thread_result);
    printf("Message is %s\n", global_message);
    exit(EXIT_SUCCESS);
}

// Function to be executed by the thread
void *thread_function(void *arg) {
    // Cast the argument back to char pointer to get the message
    char *message = (char *)arg;
    printf("thread_function is running. Argument: %s\n", message);
    sleep(3);

    // Modify the global_message from the thread
    strcpy(global_message, "\tgood bye!");

    // Exit the thread and return a message
    pthread_exit("Thank you for the CPU time");
}

