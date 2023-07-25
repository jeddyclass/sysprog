#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    const char *filename = "example_file.txt";
    const char *data = "Hello, world!\n";

    // Open the file in write mode
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    fprintf(file, "%s", data);

    // Flush data to the file using fflush()
    if (fflush(file) != 0) {
        perror("Error flushing data to file");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    
    /***
    After writing the data, use fflush() to ensure that the data is flushed to the file.
    fflush() is often used when you need to ensure that the data is immediately written to the file, without waiting for the buffer to be filled.
    It is commonly used in situations where you want to make sure that the data is persisted on disk for critical operations or to synchronize file updates across multiple processes.
    ***/

    // Close the file
    fclose(file);

    printf("Data written to '%s' and flushed to the file.\n", filename);
    return 0;
}

