#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {
    struct rlimit rlim;

    // Get the resource limit for the maximum number of file descriptors (RLIMIT_NOFILE)
    if (getrlimit(RLIMIT_NOFILE, &rlim) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    printf("Resource limit for maximum number of file descriptors:\n");
    printf("Soft limit: %ld\n", rlim.rlim_cur);
    printf("Hard limit: %ld\n", rlim.rlim_max);

    return 0;
}

