#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char character; 
    int input_fd, output_fd;

    input_fd = open("file.in", O_RDONLY); 
    output_fd = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while (read(input_fd, &character, 1) == 1)
        write(output_fd, &character, 1);

    exit(0);
}


