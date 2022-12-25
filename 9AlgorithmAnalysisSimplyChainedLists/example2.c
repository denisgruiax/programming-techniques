#include <stdio.h>
#include <stdlib.h>

// un element al listei
typedef struct Element
{
    int number;            // informatia utila
    struct Element *next; // camp de inlantuire catre urmatorul element
} Element;

// aloca un nou element si ii seteaza campurile corespunzatoare
Element *nou(int number, Element *next)
{
    Element *element = (Element *)malloc(sizeof(Element));
    if (!element)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    element->number = number;
    element->next = next;
    return element;
}

typedef struct
{
    Element *first;  // primul element din list
    Element *last; // ultimul element din list
} List;

void init(List *list)
{
    list->first = NULL;
    list->last = NULL;
}

// adauga un element la inceputul listei
void adaugaInceput(List *list, int number)
{
    Element *first = list->first;
    list->first = nou(number, first);
    if (!first)
    { // list initiala vida - trebuie setat si last pe elementul adaugat
        list->last = list->first;
    }
}

// adauga un element la sfarsitul listei
void adaugaSfarsit(List *list, int number)
{
    Element *element = nou(number, NULL);
    if (list->last)
    { // adaugare in list nevida
        list->last->next = element;
    }
    else
    { // adaugare in list vida
        list->first = element;
    }
    list->last = element;
}

void afisare(List *list)
{
    Element *current;
    for (current = list->first; current; current = current->next)
    {
        printf("%d ", current->number);
    }
    putchar('\n');
}

// elibereaza memoria ocupata de o list
void eliberare(List *list)
{
    Element *container, *current = list->first;
    while (current)
    {
        container = current->next;
        free(current);
        current = container;
    }
}

int main()
{
    List list;
    init(&list);
    adaugaSfarsit(&list, 108);
    adaugaSfarsit(&list, -1);
    adaugaSfarsit(&list, 49);
    afisare(&list);
    eliberare(&list);
    return 0;
}
