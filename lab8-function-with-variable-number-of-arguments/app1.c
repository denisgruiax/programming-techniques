/*
    Aplicația 8.1: Să se modifice exemplul 2 astfel încat funcția err să încapsuleze și condiția de eroare.
    Pentru aceasta, ea primește în plus pe prima poziție o variabilă de tip int care reprezintă o valoare logică.
    Dacă valoarea este true, se va executa err ca în exemplu, altfel err nu va avea niciun efect.
    Exemplu de folosire: err(n<=0||n>100,"n invalid: %d\n",n);    // fără if în față, deoarece err încapsulează condiția
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void err(int condition, const char *fmt, ...)
{
    if (condition)
    {

        va_list va;        // pointer la lista de argumente variabile (varargs)
        va_start(va, fmt); // va trebuie initializat cu ultimul argument fix al functiei
        fprintf(stderr, "eroare: ");
        vfprintf(stderr, fmt, va); // varianta de fprintf care primeste o lista de argumente variabile
        va_end(va);                // dupa folosirea argumentelor variabile, trebuie apelat va_end
        fputc('\n', stderr);
        exit(EXIT_FAILURE);
    }
}

int main()
{
    err(0, "%d %s", 5, "denis");
    return 0;
}