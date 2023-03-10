#include <stdio.h>

int main(int argc, char *argv[])
{
    int i;

    printf("Avem %d parametri din linia de comanda.\n", argc);
    
    for (i = 0; i < argc; i++)
        printf("Parametrul %i: '%s'\n", i, argv[i]); // un parametru este un sir de caractere, deci folosim %s
    return 0;
}