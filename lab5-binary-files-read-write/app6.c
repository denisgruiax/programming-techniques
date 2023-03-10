/*
    Aplicația 5.6: Să se scrie un program care primește 2 fișiere în linia de comandă și le compară între ele.
    Pentru fiecare octet diferit găsit, se afișează offsetul acestuia și valorile sale din fiecare fișier, în hexazecimal,
    pe câte 2 cifre. Dacă fișierele sunt de dimensiuni diferite, în final se vor afișa toți octeții din fișierul mai mare.
    Dacă fișierele sunt identice, programul nu va afișa nimic.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 1

void checkPointer(const void *pointer);
FILE *openFile(char *path);
char *readFile(FILE *file);

int main(int counter, char *arguments[])
{
    FILE *file1, *file2;
    char *bytesFromFile1, *bytesFromFile2;

    file1 = openFile(arguments[1]);
    file2 = openFile(arguments[2]);

    bytesFromFile1 = readFile(file1);
    bytesFromFile2 = readFile(file2);
    size_t length1 = strlen(bytesFromFile1), length2 = strlen(bytesFromFile2);

    if (length1 == length2)
    {
        for (size_t i = 0; i <= length1; i++)
            if (bytesFromFile1[i] != bytesFromFile2[i])
                printf("offset = %lu - value1 = %.2x - value2 = %.2x\n", i, bytesFromFile1[i], bytesFromFile2[i]);

        puts("DONE1!");
    }
    else if (length1 > length2)
    {
        for (size_t i = 0; i <= length1; i++)
            printf("offset = %lu - value1 = %.2x\n", i, bytesFromFile1[i]);

        puts("DONE2!");
    }
    else
    {
        for (size_t i = 0; i <= length2; i++)
            printf("offset = %lu - value1 = %.2x\n", i, bytesFromFile2[i]);

        puts("DONE2!");
    }

    free(bytesFromFile1);
    free(bytesFromFile2);

    fclose(file1);
    fclose(file2);

    return 0;
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

void checkPointer(const void *pointer)
{
    if (!pointer)
    {
        fprintf(stderr, "Error, pointer is null! %u\n", __LINE__);
        exit(EXIT_FAILURE);
    }
}