/*
    Aplicația 5.8: Să se scrie un program care primește în linia de comandă un nume de fișier și o serie de octeți,
    dați în hexazecimal. Programul va afișa toate pozițiile din fișier la care se află secvența de octeți specificați.
    Exemplu: ./cautare 1.dat 01 aa b2 45        -> caută în fișierul 1.dat secvența {01, aa, b2, 45} și afișează toate
    pozițiile la care o găsește

        example: "denis are mere are mere pere are alex alex denis."
        cauta: "are"
        iesire: 6->10
                15->19
                29->33
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1

void checkPointer(const void *pointer);
FILE *openFile(char *path);
char *readFile(FILE *file);
void compareBytes(char *bytes, int counter, char *arguments[]);

int main(int counter, char *arguments[])
{
    FILE *file;
    char *bytes;

    file = openFile(arguments[1]);
    checkPointer(file);

    bytes = readFile(file);
    checkPointer(bytes);

    compareBytes(bytes, counter, arguments);

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

    if (!(file = fopen(path, "rb")))
    {
        fprintf(stderr, "Error on opening the first file! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    return file;
}

char *readFile(FILE *file)
{
    char character = 0, *bytes = (char *)calloc(sizeof(char), 1);
    size_t length = 0;

    for (;;)
    {
        if (fread(&character, sizeof(char), BLOCK_SIZE, file) == BLOCK_SIZE)
        {
            bytes[length] = character;
            length++;
            bytes = (char *)realloc(bytes, sizeof(char) * (length + 1));
            checkPointer(bytes);
        }
        else
            break;
    }

    return bytes;
}

void compareBytes(char *bytes, int counter, char *arguments[])
{

    for (size_t i = 0; i <= strlen(bytes) - counter; i++)
    {
        if (*(bytes + i) == (char)strtol(*(arguments + 2), NULL, 16))
            for (size_t j = 1, flag = 2; j < counter - 2; j++, flag++)
            {
                if (*(bytes + i + j) != (char)strtol(*(arguments + j + 2), NULL, 16))
                    break;

                if (flag == counter - 2)
                    printf("%li->%li\n", i, i + counter - 1);
            }
    }
}