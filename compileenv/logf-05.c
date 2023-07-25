#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file_ptr; // File pointer to handle the file

    file_ptr = fopen("no_exist_file", "r");
    if (!file_ptr)
        syslog(LOG_ERR | LOG_USER, "oops - %m\n");
    exit(0);
}

