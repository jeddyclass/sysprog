#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    time_t current_time;

    (void)time(&current_time);
    printf("The date is: %s", ctime(&current_time));
    exit(0);
}

