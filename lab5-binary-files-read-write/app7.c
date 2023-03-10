/*
     Un program primește în linia de comandă un nume de fișier, un offset dat
     în hexazecimal și apoi o serie de octeți, specificați tot în hexazecimal.
     Programul va scrie în fișierul specificat, începând de la offsetul dat toți
     octeții primiți în linia de comandă. Restul fișierului va rămâne nemodificat.
    Exemplu: ./inlocuire 1.dat 4a0f 9e b0 51
    -> scrie octeții {9e, b0, 51} în fișierul 1.dat, începând cu poziția 4a0f
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1

void checkPointer(const void *pointer);
FILE *openFile(char *path);
void writeFile(FILE *file, int offset, int counter, char *arguments[]);

int main(int counter, char *arguments[])
{
    FILE *file;

    file = openFile(arguments[1]);

    writeFile(file, (int)strtol(arguments[2], NULL, 16), counter, arguments);

    fclose(file);

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

FILE *openFile(char *path)
{
    FILE *file;

    if (!(file = fopen(path, "rb+")))
    {
        fprintf(stderr, "Error on opening the first file! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    return file;
}

void writeFile(FILE *file, int offset, int counter, char *arguments[])
{
    for (size_t i = 3; i < counter; i++)
    {
        fseek(file, offset++, SEEK_SET);

        char value = (char)strtol(*(arguments + i), NULL, 16);
        if (fwrite(&value, sizeof(char), BLOCK_SIZE, file) == BLOCK_SIZE)
            continue;
    }
}