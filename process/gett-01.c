#include <stdio.h>
#include <unistd.h>

int main() {
    // getpid(): Get the process ID (PID) of the current process.
    pid_t my_pid = getpid();
    printf("My PID: %d\n", my_pid);

    // getppid(): Get the parent process ID (PPID) of the current process.
    pid_t parent_pid = getppid();
    printf("My Parent PID: %d\n", parent_pid);

    // getpgrp(): Get the process group ID (PGID) of the current process.
    pid_t my_pgid = getpgrp();
    printf("My Process Group ID (PGID): %d\n", my_pgid);

    // getpgid(): Get the process group ID (PGID) of a specified process (in this case, the parent process).
    pid_t parent_pgid = getpgid(parent_pid);
    printf("My Parent's Process Group ID (PGID): %d\n", parent_pgid);

    return 0;
}

