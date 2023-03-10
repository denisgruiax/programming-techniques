#include <stdio.h>
#include <stdlib.h>

void stelute(int n)
{
    while (n--)
        printf("*");
}

void spatii(int n)
{
    while (n--)
        printf(" ");
}

int main(int argc, char *argv[])
{
    int i, n;
    // se incepe de la 1, pentru a nu se considera si numele programului
    for (i = 1; i < argc; i++)
    {
        n = atoi(argv[i]);
        // numerele de la pozitii impare sunt considerate stelute, iar cele de la pozitii pare spatii
        if (i % 2 == 1)
            stelute(n);
        else
            spatii(n);
    }
    printf("\n");

    return 0;
}