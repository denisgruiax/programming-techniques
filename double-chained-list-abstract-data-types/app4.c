/*
    Aplicația 10.4: Folosind TDA-ul LISTAD să se declare două tipuri de liste: una care conține elemente de tip int
    și alta care conține elemente de tip double. Se citesc de la tastatură numere reale până când se tastează 0.
    Dacă numerele nu au parte zecimală, se vor depune în prima listă, altfel în cea de a doua.
    În final se vor afișa ambele liste.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Element
{
    union Number
    {
        int integer;
        double real;
    } number;

    struct Element *previous;
    struct Element *next;
} Element;

#define LIST_AD_NUME List       // numele TDA
#define LIST_AD_ELEMENT Element // tipul unui element din lista

#include "app4.h"

Element *new_integer(const int integer)
{
    Element *element = (Element *)malloc(sizeof(Element));
    if (!element)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }

    element->number.integer = integer;

    return element;
}

void display_integers(Element *integers)
{
    printf("integers\n");
    for (Element *interator = integers; interator; interator = interator->next)
        printf("%i ", interator->number.integer);

    putchar('\n');
}

Element *new_real(const double real)
{
    Element *element = (Element *)malloc(sizeof(Element));
    if (!element)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }

    element->number.real = real;

    return element;
}

void display_reals(Element *reals)
{
    printf("reals\n");
    for (Element *interator = reals; interator; interator = interator->next)
        printf("%.2lf ", interator->number.real);

    putchar('\n');
}

int main()
{
    int integer = 0;
    double real = 0.0, fractionalPart = 0.0;
    Element *element = NULL;
    List integers = {0}, reals = {0};

    List_initialize(&integers);
    List_initialize(&reals);

    printf("Insert numbers.\n");

    do
    {
        scanf("%lf", &real);

        fractionalPart = real - ceil(real);

        if (real > 0.0)
        {
            if (fractionalPart == 0.00)
            {
                integer = (int)ceil(real);
                element = new_integer(integer);
                List_add(&integers, element);
            }
            else
            {
                element = new_real(real);
                List_add(&reals, element);
            }
        }

    } while (real != 0);

    display_integers(integers.first);
    display_reals(reals.first);

    List_freeMemory(&integers);
    List_freeMemory(&reals);

    return 0;
}