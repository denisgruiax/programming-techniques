/*
    Aplicația 8.5: Să se implementeze o funcție input(const char *fmt,...). În șirul fmt pot fi caractere obișnuite
    (orice în afară de %) și placeholdere (% urmat de o literă). Pentru fiecare placeholder posibil
    ( %d - int, %f -float, %c - char ), în lista de argumente variabile se va afla adresa unei variabile de
    tipul corespunzător. Funcția afișează pe ecran caracterele obișnuite și citește de la tastatură pentru placeholdere.
    Exemplu: input("n=%dch=%c",&n,&character);	// citește o valoare de tip int în n și de tip char în character
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

void input(const char *format, ...)
{
    va_list variableArguments;           // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, format); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    while (*format != '\0')
    {
        if (*format == '%')
            switch (*(format + 1))
            {
            case 'c':
                printf("character = ");
                scanf(" %c", va_arg(variableArguments, char *));
                break;

            case 'd':
                printf("decimal = ");
                scanf("%i", va_arg(variableArguments, int *));
                break;

            default:
                break;
            }

        format++;
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end
}

int main()
{
    char character = 0;
    int decimal = 0;

    input("decimal = %d, character = %c", &decimal, &character);

    printf("%d %c", decimal, character);

    return 0;
}