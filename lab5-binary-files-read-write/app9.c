/*
    Aplicația 5.9: Să se scrie un program care primește o serie de n programe în linia de comandă și
    le concatenează pe primele n-1 într-un nou fișier având numele specificat pe ultima poziție din linia de comandă.

    Exemplu: ./concat 1.dat 2.dat 3.dat rez.dat       ->
        concatenează conținutul fișierelor {1.dat, 2.dat, 3.dat} într-un nou fișier, denumit rez.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1

void checkPointer(const void *pointer);
FILE *openFileForReading(char *path);
FILE *openFileForWriting(char *path);

int main(int counter, char *arguments[])
{
    char character = 0;
    FILE *input = NULL, *output = NULL;

    checkPointer(output = openFileForWriting(*(arguments + 1)));

    for (size_t i = 2; i < counter; i++)
    {
        checkPointer(input = openFileForReading(*(arguments + i)));

        for (;;)
        {
            if (fread(&character, sizeof(char), BLOCK_SIZE, input) == BLOCK_SIZE)
                fwrite(&character, sizeof(char), BLOCK_SIZE, output);
            else
                break;
        }
    }

    return 0;
}

void checkPointer(const void *pointer)
{
    if (!pointer)
    {
        fprintf(stderr, "Error, pointer is null! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }
}

FILE *openFileForReading(char *path)
{
    FILE *file;

    if (!(file = fopen(path, "rb")))
    {
        fprintf(stderr, "Error on opening the first file! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    return file;
}

FILE *openFileForWriting(char *path)
{
    FILE *file;

    if (!(file = fopen(path, "ab")))
    {
        fprintf(stderr, "Error on opening the first file! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    return file;
}