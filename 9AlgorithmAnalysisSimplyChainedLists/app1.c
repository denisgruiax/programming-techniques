/*
    Aplicația 9.1: Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt identice, altfel 0.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int number;
    struct Element *next;
} Element;

Element *new(int number, Element *next);
Element *addElementToTheBeginning(Element *elements, int number);
void displayElements(Element *elements);
void freeMemory(Element *elements);
size_t length(Element *elements);
int compareLists(Element *elements, Element *elements2);

int main()
{
    Element *elements = new (99, new (101, NULL));
    Element *elements2 = new (104, new (99, new (101, NULL)));

    /*UNIT TESTING*/

    printf("%i\n", compareLists(elements, elements2));

    elements = new (105, new (99, new (101, NULL)));
    elements2 = new (104, new (99, new (101, NULL)));
    printf("%i\n", compareLists(elements, elements2));

    elements = new (104, new (99, new (101, NULL)));
    elements2 = new (104, new (100, new (101, NULL)));
    printf("%i\n", compareLists(elements, elements2));

    elements = new (104, new (99, new (100, NULL)));
    elements2 = new (104, new (99, new (101, NULL)));
    printf("%i\n", compareLists(elements, elements2));

    elements = new (104, new (99, new (101, NULL)));
    elements2 = new (104, new (99, new (101, NULL)));
    printf("%i\n", compareLists(elements, elements2));

    freeMemory(elements);
    freeMemory(elements2);

    return 0;
}

Element *new(int number, Element *next)
{
    Element *element = (Element *)malloc(sizeof(Element));

    if (!element)
    {
        printf("Error on allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    element->number = number;
    element->next = next;

    return element;
}

Element *addElementToTheBeginning(Element *elements, int number)
{
    return new (number, elements);
}

void displayElements(Element *elements)
{
    for (; elements; elements = elements->next)
        printf("%d ", elements->number);

    putchar('\n');
}

void freeMemory(Element *elements)
{
    Element *next;

    while (elements)
    {
        next = elements->next;
        free(elements);
        elements = next;
    }
}

size_t length(Element *elements)
{
    size_t counter = 0;
    struct Element *current = NULL;

    for (current = elements; current; current = current->next)
        counter++;

    return counter;
}

int compareLists(Element *elements, Element *elements2)
{
    /*
        If line 110 is executed, then the complexity is O(1).

        If line 116 is executed, then the compelxity is between O(1) and O(n-1).

        If line 120 is executed, then the complexity is O(n);
    */

    if (length(elements) != length(elements2))
        return 0;

    Element *current = NULL, *current2 = NULL;

    for (current = elements, current2 = elements2; current; current = current->next, current2 = current2->next)
        if (current->number != current2->number)
            return 0;

    return 1;
}