#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int num) {
    write(STDOUT_FILENO, "hey hey, I can not die...\n", 28);
}

int main()
{
    signal(SIGINT, handler);

    while (1)
    {
        printf("inf loop ..., pid:[%d]\n", getpid());
        sleep(1);
    }
    return 0;
}

