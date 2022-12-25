#include <stdio.h>
#include <stdlib.h>

// un element al listei
typedef struct Element
{
    int number;                  // informatia utila
    struct Element *next; // camp de inlantuire catre urmatorul element
} Element;

// aloca un new element si ii seteaza campurile corespunzatoare
Element *new(int number, Element *next)
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

// adauga un element la inceputul listei
// returneaza noua lista
Element *addElementToTheBeginning(Element *lista, int number)
{
    return new(number, lista);
}

// adauga un element la sfarsitul listei
// returneaza noua lista
Element *addElementToTheEnd(Element *lista, int number)
{
    if (!lista)
        return new(number, NULL);
    Element *currentList = lista, *next;

    for (next = currentList->next; next; currentList = next, next = currentList->next)
    {
    }

    currentList->next = new(number, NULL);

    return lista;
}

void displayElements(Element *lista)
{
    for (; lista; lista = lista->next)
    {
        printf("%d ", lista->number);
    }
    putchar('\n');
}

// elibereaza memoria ocupata de o lista
void freeMemory(Element *lista)
{
    Element *container;

    while (lista)
    {
        container = lista->next;
        free(lista);
        lista = container;
    }
}

// deleteElement un element din lista
// returneaza noua lista
// folosire:  lista=deleteElement(lista, numar);

Element *deleteElement(Element *lista, int number)
{
    Element *previous; // predecesor
    Element *current;  // element curent

    for (previous = NULL, current = lista; current; previous = current, current = current->next)
    {
        if (current->number == number)
        {
            if (previous == NULL)
            { // deleteElement primul element din lista
                lista = lista->next;
            }
            else
            { // deleteElement un element din interiorul listei
                previous->next = current->next;
            }

            free(current);

            return lista;
        }
    }
    return lista; // nu s-a gasit elementul in lista
}

int main()
{
    // varianta 1: construieste direct lista dorita

    Element *lista1 = new(108, new(-1, new(49, NULL)));

    displayElements(lista1);
    freeMemory(lista1);

    // varianta 2: adauga la inceputul listei elementele in ordinea inversa

    Element *lista2 = NULL;

    lista2 = addElementToTheBeginning(lista2, 49);
    lista2 = addElementToTheBeginning(lista2, -1);
    lista2 = addElementToTheBeginning(lista2, 108);

    displayElements(lista2);
    freeMemory(lista2);

    // varianta 3: adauga la sfarsitul listei

    Element *lista3 = NULL;

    lista3 = addElementToTheEnd(lista3, 49);
    lista3 = addElementToTheEnd(lista3, -1);
    lista3 = addElementToTheEnd(lista3, 108);

    displayElements(lista3);
    freeMemory(lista3);

    return 0;
}
