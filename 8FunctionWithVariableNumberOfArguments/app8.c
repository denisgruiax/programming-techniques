/*

    Aplicația 8.8: Să se scrie o funcție sortare(int n,...) care pe prima poziție are numărul

    de elemente de sortat, iar pe următoarele poziții n adrese de valori de tip int.

    Funcția va sorta crescător valorile de la adresele date.

    Exemplu: sortare(3,&i,&j,&k);           // sortează crescător valorile lui i, j și k

*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void sort(int counter, ...)
{
    int *values = (int *)calloc(sizeof(int), counter);
    int temp = 0;

    va_list variableArguments;
    va_start(variableArguments, counter);

    for (size_t i = 0; i < counter; i++)
        *(values + i) = *va_arg(variableArguments, int *);

    va_end(variableArguments);

    for (size_t i = 0; i < counter; i++)
        printf("%i ", *(values + i));
    puts("\n");

    for (size_t i = 0; i < counter; i++)
        for (size_t j = 0; j < counter - 1; j++)
            if (*(values + j) > *(values + j + 1))
            {
                temp = *(values + j);
                *(values + j) = *(values + j + 1);
                *(values + j + 1) = temp;
            }

    va_start(variableArguments, counter);

    for (size_t i = 0; i < counter; i++)
        *va_arg(variableArguments, int *) = *(values + i);

    va_end(variableArguments);
}

int main()
{
    int x = 3, y = 1, z = 2, k = 0;
    sort(4, &x, &y, &z, &k);

    printf("%i %i %i %i\n", x, y, z, k);

    return 0;
}