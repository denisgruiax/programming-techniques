/*
    Aplicația 8.3: Să se scrie o funcție absN(int n,...) care primește un număr n de adrese de tip
    float și setează la fiecare dintre aceste adrese valoarea absolută de la acea locație.
    Exemplu: absN(2,&x,&y);		// echivalent cu x=fabs(x); y=fabs(y);
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

void absoluteValue(int counter, ...)
{
    double *value = NULL;

    va_list variableArguments;            // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, counter); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    while (--counter)
    {
        value = va_arg(variableArguments, double *);
        *value < 0 ? *value = -*value : *value;
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end
}

int main()
{
    double x = -1.2, y = 1.3;

    absoluteValue(2, &x, &y);

    printf("%0.2lf %0.2lf\n", x, y);

    return 0;
}