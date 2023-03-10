/*
Aplicația 1.7: Scrieți un program care calculează suma parametrilor primiți din linia de comandă (numere reale).
Exemplu: execuția fără parametri va fișa 0, iar execuția cu parametrii 1.1 6.57 99.122 va afișa 106.792
*/

#include <stdio.h>
#include <stdlib.h>

int main(int counter, char *arguments[])
{
    double sum = 0.0;

    if (counter > 1)
        for (unsigned count = 1; count < counter; count++)
            sum += atof(arguments[count]);

    printf("%0.3f\n", sum);
    return 0;
}