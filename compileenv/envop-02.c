//  1  The main function accepts command-line arguments argc and argv to handle environment variables in the program, envop.c.
//     usage: evnop ENVNEW abc
//            evnop HOME

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *var, *value;

    //  Check if the program has been called correctly with valid arguments.
    if (argc == 1 || argc > 3) {
        fprintf(stderr, "Usage: environ var [value]\n");
        exit(1);
    }

    //  Fetch the value of the specified variable from the environment using the getenv function.
    var = argv[1];
    value = getenv(var);
    if (value)
        printf("Variable %s has value %s\n", var, value);
    else
        printf("Variable %s has no value\n", var);

    //  Check if the program was called with a second argument.
    //  If so, set the variable to the provided value using putenv.
    if (argc == 3) {
        char *string;
        value = argv[2];
        // Allocate memory to construct the new environment variable string in the form "name=value".
        string = malloc(strlen(var) + strlen(value) + 2);
        if (!string) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        strcpy(string, var);
        strcat(string, "=");
        strcat(string, value);
        printf("Calling putenv with: %s\n", string);
        // Set the environment variable using putenv.
        if (putenv(string) != 0) {
            fprintf(stderr, "putenv failed\n");
            free(string);
            exit(1);
        }

        //  After setting the new environment variable, fetch and display its updated value using getenv.
        value = getenv(var);
        if (value)
            printf("New value of %s is %s\n", var, value);
        else
            printf("New value of %s is null??\n", var);
    }
    exit(0);
}

