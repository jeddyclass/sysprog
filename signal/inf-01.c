#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    while (1)
    {
        printf("inf loop ..., pid:[%d] \n", getpid());
        sleep(1);
    }
    return 0;
}



