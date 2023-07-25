#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char host_name[256]; // Buffer to store the host name
    struct utsname host_info; // Structure to store system information

    // Get the host name using gethostname() and store it in the 'host_name' buffer
    if (gethostname(host_name, 255) != 0 || uname(&host_info) < 0) {
        // If getting host information fails, print an error message and exit the program
        fprintf(stderr, "Could not get host information\n");
        exit(1);
    }

    // Print the obtained host information
    printf("Computer host name is %s\n", host_name);
    printf("System is %s on %s hardware\n", host_info.sysname, host_info.machine);
    printf("Nodename is %s\n", host_info.nodename);
    printf("Version is %s, %s\n", host_info.release, host_info.version);
    exit(0);
}

