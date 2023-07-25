/* main.c */
#include <stdlib.h>
#include "a.h"

extern void function_p2();
extern void function_p3();

int main()
{
    function_p2();
    function_p3();
    exit (EXIT_SUCCESS);
}

