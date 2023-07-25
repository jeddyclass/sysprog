#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;

    // Get the resource limit for CPU time (RLIMIT_CPU)
    if (getrlimit(RLIMIT_CPU, &rlim) == -1) {
        perror("getrlimit: RLIMIT_CPU");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for CPU time:\n");
    printf("Soft limit: %ld seconds\n", rlim.rlim_cur);
    printf("Hard limit: %ld seconds\n", rlim.rlim_max);

    // Get the resource limit for file size (RLIMIT_FSIZE)
    if (getrlimit(RLIMIT_FSIZE, &rlim) == -1) {
        perror("getrlimit: RLIMIT_FSIZE");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for file size:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for data segment size (RLIMIT_DATA)
    if (getrlimit(RLIMIT_DATA, &rlim) == -1) {
        perror("getrlimit: RLIMIT_DATA");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for data segment size:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for stack size (RLIMIT_STACK)
    if (getrlimit(RLIMIT_STACK, &rlim) == -1) {
        perror("getrlimit: RLIMIT_STACK");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for stack size:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for core file size (RLIMIT_CORE)
    if (getrlimit(RLIMIT_CORE, &rlim) == -1) {
        perror("getrlimit: RLIMIT_CORE");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for core file size:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for resident set size (RLIMIT_RSS)
    if (getrlimit(RLIMIT_RSS, &rlim) == -1) {
        perror("getrlimit: RLIMIT_RSS");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for resident set size:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for number of processes (RLIMIT_NPROC)
    if (getrlimit(RLIMIT_NPROC, &rlim) == -1) {
        perror("getrlimit: RLIMIT_NPROC");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for number of processes:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    // Get the resource limit for number of open files (RLIMIT_NOFILE)
    if (getrlimit(RLIMIT_NOFILE, &rlim) == -1) {
        perror("getrlimit: RLIMIT_NOFILE");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for number of open files:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    // Get the resource limit for locked memory address space (RLIMIT_MEMLOCK)
    if (getrlimit(RLIMIT_MEMLOCK, &rlim) == -1) {
        perror("getrlimit: RLIMIT_MEMLOCK");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for locked memory address space:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for address space (RLIMIT_AS)
    if (getrlimit(RLIMIT_AS, &rlim) == -1) {
        perror("getrlimit: RLIMIT_AS");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for address space:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for file locks (RLIMIT_LOCKS)
    if (getrlimit(RLIMIT_LOCKS, &rlim) == -1) {
        perror("getrlimit: RLIMIT_LOCKS");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for file locks:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    // Get the resource limit for pending signals (RLIMIT_SIGPENDING)
    if (getrlimit(RLIMIT_SIGPENDING, &rlim) == -1) {
        perror("getrlimit: RLIMIT_SIGPENDING");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for pending signals:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    // Get the resource limit for size of POSIX message queues (RLIMIT_MSGQUEUE)
    if (getrlimit(RLIMIT_MSGQUEUE, &rlim) == -1) {
        perror("getrlimit: RLIMIT_MSGQUEUE");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for size of POSIX message queues:\n");
    printf("Soft limit: %ld bytes\n", rlim.rlim_cur);
    printf("Hard limit: %ld bytes\n", rlim.rlim_max);

    // Get the resource limit for nice value (RLIMIT_NICE)
    if (getrlimit(RLIMIT_NICE, &rlim) == -1) {
        perror("getrlimit: RLIMIT_NICE");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for nice value:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    // Get the resource limit for real-time priority (RLIMIT_RTPRIO)
    if (getrlimit(RLIMIT_RTPRIO, &rlim) == -1) {
        perror("getrlimit: RLIMIT_RTPRIO");
        exit(EXIT_FAILURE);
    }
    printf("Resource limit for real-time priority:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    return 0;
}

