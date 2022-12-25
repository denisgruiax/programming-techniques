/*
    Aplicația 9.2: Să se scrie o funcție care primește o listă și returnează lista respectivă cu elementele inversate.
    Funcția va acționa doar asupra listei originare, fără a folosi vectori sau alocare de noi elemente.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Element
{
    int number;
    struct Element *next;
} Element;

Element *new(int number, Element *next);
Element *addElementToTheBeginning(int number, Element *elements);
void displayElements(Element *elements);
void freeMemory(Element *elements);
Element *reverseList(Element *elements);

int main()
{
    Element *elements = new (105, new (99, new (101, NULL)));

    displayElements(elements);

    elements = reverseList(elements);
    displayElements(elements);

    freeMemory(elements);

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

Element *addElementToTheBeginning(int number, Element *elements)
{
    return new (number, elements);
}

void displayElements(Element *elements)
{
    Element *current = elements;
    for (; current; current = current->next)
        printf("%i ", current->number);

    putchar('\n');
}

void freeMemory(Element *elements)
{
    Element *next = NULL;

    while (elements)
    {
        next = elements->next;
        free(elements);
        elements = next;
    }
}

Element *reverseList(Element *elements)
{
    /*
        1->2->3->4->NULL

        1<-2 3->4->NULL
        NULL<-1<-2<-3 4->NULL

        NULL<-1<-2<-3<-4
    */

    Element *previous = NULL, *next = NULL;

    while (elements)
    {
        next = elements->next;
        
        elements->next = previous;
        previous = elements;
        
        elements = next;
    }

    return previous;
}