/*
    Aplicația 8.2: Să se scrie o funcție double *allocVec(int n,...) care primește pe prima
    poziție un număr de elemente iar apoi n elemente reale. Funcția variableArguments aloca dinamic un vector
    de tip double în care variableArguments depune toate elementele.
Exemplu: allocVec(3,7.2,-1,0)		=> {7.2, -1, 0}
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

double *allocateVectorOfFloatNumbers(int length, ...)
{
    double *numbers = (double *)calloc(sizeof(double), length + 1);

    va_list variableArguments;           // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, length); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    for (size_t i = 0; i < length; i++)
    {
        *(numbers + i) = va_arg(variableArguments, double);
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end

    return numbers;
}

int main()
{
    double *numbers = allocateVectorOfFloatNumbers(5, 1.2, 1.3, 1.4, 1.5, 1.6);

    for (size_t i = 0; i < 5; i++)
        printf("%0.2lf ", *(numbers + i));

    return 0;
}