#include <unistd.h>
#include <stdlib.h>

int main()
{
    const char data[] = "Here is some data, wala, wala... \n";
    const int data_size = sizeof(data) - 1; // Exclude the null terminator

    if ((write(1, data, data_size)) != data_size)
        write(2, "A write error has occurred on file descriptor 1\n", 46);

    exit(0);
}


