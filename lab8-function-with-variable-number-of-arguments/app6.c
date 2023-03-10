/*
    Aplicația 8.6: Să se scrie o funcție char *concat(int n,...) care primește un număr de șiruri de caractere și
    apoi șirurile propriu-zise. Funcția va concatena într-un nou șir, alocat dinamic, conținuturile tuturor șirurilor date,
    cu câte un spațiu între ele și va returna acest șir.
Exemplu: concat(3,”Ion”,”si”,”Ana”)		=> “Ion si Ana”
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

char *concat(int size, ...)
{
    char *reference = NULL, *container = NULL;
    size_t numberOfBytes = 1;

    container = (char *)calloc(sizeof(char), numberOfBytes);

    va_list variableArguments;         // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, size); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    reference = va_arg(variableArguments, char *);
    numberOfBytes += strlen(reference);

    container = (char *)realloc(container, sizeof(char) * (numberOfBytes + 1)); //+1 for every space between strings
    strcat(container, reference);

    while (--size)
    {
        reference = va_arg(variableArguments, char *);
        numberOfBytes += strlen(reference);

        container = (char *)realloc(container, sizeof(char) * (numberOfBytes + 1)); //+1 for every space between strings
        strcat(container, " ");
        strcat(container, reference);
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end

    return container;
}

int main()
{
    char *test = concat(3, "Ion", "si", "Ana");
    puts(test);

    return 0;
}