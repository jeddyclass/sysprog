#include <stdio.h>
#include <stdlib.h>

int main() {
    char command[] = "ls -l"; // Example command to list files in the current directory

    printf("Running command: %s\n", command);
    int exit_code = system(command);

    if (exit_code == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }

    printf("Command completed with exit code: %d\n", exit_code);

    return 0;
}

