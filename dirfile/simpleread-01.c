#include <unistd.h>
#include <stdlib.h>

int main()
{
    char input_buffer[1280];
    int bytes_read;

    bytes_read = read(0, input_buffer, 1280);
    if (bytes_read == -1)
        write(2, "A read error has occurred\n", 26);

    if ((write(1, input_buffer, bytes_read)) != bytes_read)
        write(2, "A write error has occurred\n", 27);

    exit(0);
}


