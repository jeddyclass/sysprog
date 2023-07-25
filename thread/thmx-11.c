//massive thread

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 6

void* thread_function(void* arg);

int main() {
    int res;
    pthread_t thread_ids[NUM_THREADS];
    void* thread_result;
    int thread_args[NUM_THREADS]; // Array to store thread arguments
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        thread_args[i] = i; // Assign a unique number as an argument for each thread

        res = pthread_create(&thread_ids[i], NULL, thread_function, &thread_args[i]);
        if (res != 0) {
            perror("Thread creation failed");
            exit(EXIT_FAILURE);
        }
        sleep(1);
    }

    printf("Waiting for threads to finish...\n");
    for (i = NUM_THREADS - 1; i >= 0; i--) {
        res = pthread_join(thread_ids[i], &thread_result);
        if (res == 0) {
            printf("Picked up a thread[%d]\n",i);
        } else {
            perror("pthread_join failed");
        }
    }

    printf("All done\n");
    exit(EXIT_SUCCESS);
}

void* thread_function(void* arg) {
    int my_number = *(int*)arg;
    int rand_num;

    printf("Thread %d is running.\n", my_number);
    rand_num = 1 + (int)(9.0 * rand() / (RAND_MAX + 1.0));
    sleep(rand_num);
    printf("Bye from %d\n", my_number);

    pthread_exit(NULL);
}

