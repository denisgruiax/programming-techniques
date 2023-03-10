/*
    Aplicația 5.2: Scrieți un program care copiază conținutul unui fișier sursă într-un fișier destinație.
    Numele fișierelor se citesc din linia de comandă. Pentru eficiența copierii, programul va citi câte un bloc de
    maxim 4096 de octeți, pe care îl va scrie în destinație.
    Exemplu: ./copiere src.dat dst.dat                    -> copiază src.dat în dst.dat
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 4096

int main(int counter, char *arguments[])
{
    FILE *input = NULL, *output = NULL;
    size_t sizeOfInput = 0, sizeOfOutput = 0;
    char bytes[BLOCK_SIZE];

    if (!(input = fopen(arguments[1], "rb")))
    {
        fprintf(stderr, "Error on opening the input file.\n");
        exit(EXIT_FAILURE);
    }

    if (!(output = fopen(arguments[2], "wb")))
    {
        fprintf(stderr, "Error on opening the output file.\n");
        exit(EXIT_FAILURE);
    }

    do
    {
        sizeOfInput = fread(bytes, sizeof(char), BLOCK_SIZE, input);

        if (sizeOfInput)
        {
            sizeOfOutput = fwrite(bytes, sizeof(char), BLOCK_SIZE, output);
        }
    } while ((sizeOfInput == sizeOfOutput) && (sizeOfInput > 0));

    return 0;
}