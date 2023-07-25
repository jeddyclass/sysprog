#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>  // Include the <string.h> header for strlen()

int main() {
    int fd;
    const char *filename = "example_file.txt";
    const char *data = "Hello, world!\n";
    ssize_t bytes_written;

    // Open the file in write mode and create it if it doesn't exist
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write data to the file
    bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Flush data to the storage device using fsync()
    if (fsync(fd) == -1) {
        perror("Error flushing data to storage device");
        close(fd);
        exit(EXIT_FAILURE);
    }

    /****
    After writing the data, use fsync() to ensure that the data is flushed to the storage device to make it durable.
    Please note that fsync() can have a performance impact, so it should be used judiciously when data durability is critical.
    It's typically used in scenarios where you want to guarantee that the data is safely stored on disk, like in critical data logging or transactional systems.
    ****/

    // Close the file
    close(fd);

    printf("Data written to '%s' and flushed to the storage device.\n", filename);
    return 0;
}

