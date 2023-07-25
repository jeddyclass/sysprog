#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

// Function for process 1
void process1_function() {
    printf("Process 1: Starting...\n");
    
    // Access a NULL pointer to cause a segmentation fault
    int* ptr = NULL;
    *ptr = 10;
    
    // This code will not be reached due to the segmentation fault
    printf("Process 1: Exiting...\n");
}

// Function for process 2
void process2_function() {
    printf("Process 2: Starting...\n");
    
    // Sleep for a while to ensure process 1 starts first
    sleep(2);
    
    // Send a SIGSEGV signal to process 1 to cause a segmentation fault
    kill(getppid(), SIGSEGV);
    
    // This code will not be reached due to the segmentation fault
    printf("Process 2: Exiting...\n");
}

int main() {
    pid_t pid;
    
    // Create process 1
    pid = fork();
    if (pid == 0) {
        // This is process 1
        process1_function();
        return 0;
    } else if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    // Create process 2
    pid = fork();
    if (pid == 0) {
        // This is process 2
        process2_function();
        return 0;
    } else if (pid < 0) {
        perror("fork");
        return 1;
    }
    
    // Wait for both processes to finish
    int status;
    wait(&status);
    wait(&status);
    
    // The code will reach this point even if one of the processes caused a segfault
    printf("Main process: Exiting...\n");
    return 0;
}

