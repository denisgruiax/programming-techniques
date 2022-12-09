/*
    Aplicația 5.5: Să se scrie un program similar cu hexdump, care primește un nume de fișier în linia de comandă,
    citește câte 16 octeți din el și îi afișează pe câte o linie. Fiecare linie începe cu offsetul ei în fișier,
    afișat în hexazecimal pe 8 cifre cu 0 în față, după care valorile hexa ale celor 16 octeți pe câte 2 cifre și
    în final caracterele. Dacă codul unui caracter este în intervalul 32-255 se va afișa ca atare, altfel se va afișa
    un punct în locul său. Dacă ultima linie este incompletă, se va completa cu octeți de 0.
*/

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

void readFile(char *path);

int main(int counter, char *arguments[])
{
    readFile(arguments[1]);

    return 0;
}

void readFile(char *path)
{
    FILE *input = NULL;
    char bytes[BLOCK_SIZE] = {0};
    int sizeOfInput = 0;

    if (!(input = fopen(path, "rb")))
    {
        fprintf(stderr, "Error on opening the file! %i\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    do
    {
        static size_t offset = 0;

        sizeOfInput = fread(bytes, sizeof(char), BLOCK_SIZE, input);

        printf("%.8lx | ", offset);

        for (size_t i = 0; i < BLOCK_SIZE; i += 2)
            printf(" %.2x%.2x", 0xFF & bytes[i + 1], 0xFF & bytes[i]);

        printf(" | ");

        for (size_t i = 0; i < BLOCK_SIZE; i++)
        {
            if ((bytes[i] >= 32) && (bytes[i] <= 255))
                printf("%c", bytes[i]);
            else
                putchar('.');
        }

        offset += BLOCK_SIZE;

        putchar('\n');

    } while (sizeOfInput > 0);
}