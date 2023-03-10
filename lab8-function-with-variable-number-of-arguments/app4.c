/*
    Aplicația 8.4: Să se scrie o funcție crescator(int n,char tip,...) care primește un număr n de valori
    și returnează 1 dacă ele sunt în ordine strict crescătoare, altfel 0. Caracterul tip indică tipul valorilor
    și poate fi ‘d’ - int, ‘f’ - double.

    Exemplu: printf(“%d”,crescator(3,’d’,-1,7,9));
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

int strictlyMonotonous(int length, char type, ...)
{
    va_list variableArguments;         // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, type); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    int *container = (int *)calloc(sizeof(int), length + 1);
    double *container2 = (double *)calloc(sizeof(double), length + 1);

    switch (type)
    {
    case 'd':
        for (size_t i = 0; i < length; i++)
            *(container + i) = va_arg(variableArguments, int);

        for (size_t i = 0; i < length - 1; i++)
            if (*(container + i) >= *(container + i + 1))
            {
                va_end(variableArguments);
                return FALSE;
            }
        break;

    case 'f':
        for (size_t i = 0; i < length; i++)
            *(container2 + i) = va_arg(variableArguments, double);

        for (size_t i = 0; i < length - 1; i++)
            if (*(container2 + i) >= *(container2 + i + 1))
            {
                va_end(variableArguments);
                return FALSE;
            }
        break;

    default:
        fprintf(stderr, "Bad option! %u\n", __LINE__);
        exit(EXIT_FAILURE);
        break;
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end

    return TRUE;
}

int main()
{
    printf("%d\n", strictlyMonotonous(4, 'd', 1, 2, 2, 3));
    printf("%d\n", strictlyMonotonous(4, 'd', 1, 2, 3, 4));

    printf("%d\n", strictlyMonotonous(4, 'f', 1.0, 2.2, 2.2, 3.0));
    printf("%d\n", strictlyMonotonous(4, 'f', 1.0, 2.0, 3.0, 4.0));

    return 0;
}