#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

/*** Function to print the contents of a directory recursively ***/
void print_directory_contents(char *directory_path, int depth)
{
    DIR *dir_ptr;
    struct dirent *entry;
    struct stat stat_buffer;

    /*** Attempt to open the specified directory ***/
    if ((dir_ptr = opendir(directory_path)) == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", directory_path);
        return;
    }

    /*** Change the current working directory to the specified directory ***/
    chdir(directory_path);

    /*** Iterate through the directory entries ***/
  /***
  Use readdir() to iterate through the entries in the opened directory, and assign each entry to entry one by one.
  The loop continues until readdir() returns NULL, indicating the end of the directory.
  ***/
    while ((entry = readdir(dir_ptr)) != NULL) {
        /*** Get information about the file/directory ***/
        /***
        Use lstat() to retrieve information about the current directory entry (entry->d_name) and store it in stat_buffer.
    lstat() is similar to stat(), but it does not follow symbolic links.
    ***/
        lstat(entry->d_name, &stat_buffer);

        /*** Check if it is a directory using S_ISDIR macro ***/
    /***
    Check if the current entry is a directory using the S_ISDIR() macro.
    This macro checks the file type in the st_mode field of the stat structure.
    If the entry is a directory, the condition evaluates to true.
    ***/
        if (S_ISDIR(stat_buffer.st_mode)) {
            /*** Ignore "." and ".." directories ***/
            if (strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0)
                continue;

            /*** Print the directory name with appropriate indentation ***/
            printf("%*s%s/\n", depth, "", entry->d_name);

            /*** Recurse into the subdirectory with increased indentation ***/
            print_directory_contents(entry->d_name, depth + 4);
        } else {
            /*** Print the file name with appropriate indentation ***/
            printf("%*s%s\n", depth, "", entry->d_name);
        }
    }

    /*** Go back to the parent directory ***/
    chdir("..");

    /*** Close the directory stream ***/
    closedir(dir_ptr);
}

/*** Main function ***/
int main()
{
    printf("Directory scan of /tmp:\n");

    /*** Start scanning the /home directory with initial depth of 0 ***/
    print_directory_contents("/tmp", 0);

    printf("done.\n");

    exit(0);
}

