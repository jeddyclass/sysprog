#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signalHandler(int sig)
{
    printf("OUCH! - I got signal %d\n", sig);
    (void)signal(SIGINT, SIG_DFL);
}

int main()
{
    (void)signal(SIGINT, signalHandler);

    while (1) {
        printf("Hello World!\n");
        sleep(1);
    }

    return 0;
}

