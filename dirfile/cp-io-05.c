#include <stdio.h>
#include <stdlib.h>

int main()
{
    int character;
    FILE *input_file, *output_file;

    input_file = fopen("file.in", "r");
    output_file = fopen("file.out", "w");

    while ((character = fgetc(input_file)) != EOF)
        fputc(character, output_file);

    fclose(input_file);
    fclose(output_file);
    exit(0);
}

