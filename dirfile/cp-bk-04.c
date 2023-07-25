#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char buffer[1024]; 
    int input_fd, output_fd; 
    int bytes_read;

    input_fd = open("file.in", O_RDONLY); 
    output_fd = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while ((bytes_read = read(input_fd, buffer, sizeof(buffer))) > 0)
        write(output_fd, buffer, bytes_read);

    exit(0);
}

