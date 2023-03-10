/*
    Aplicația 9.4: Pentru implementarea listei care memorează adresa ultimului element, 
    să se scrie o funcție șterge, care șterge din listă un element dat.
*/

#include <stdio.h>
#include <stdlib.h>

// un element al listei
typedef struct Node
{
    int number;            // informatia utila
    struct Node *next; // camp de inlantuire catre urmatorul element
} Node;

// aloca un new element si ii seteaza campurile corespunzatoare
Node *new(int number, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    node->number = number;
    node->next = next;
    return node;
}

typedef struct
{
    Node *first;  // primul element din list
    Node *last; // ultimul element din list
} List;

void initialize(List *list)
{
    list->first = NULL;
    list->last = NULL;
}

// adauga un element la inceputul listei
void addToTheBeggining(List *list, int number)
{
    Node *first = list->first;
    list->first = new(number, first);
    if (!first)
    { // list initiala vida - trebuie setat si last pe elementul adaugat
        list->last = list->first;
    }
}

// adauga un element la sfarsitul listei
void addToTheEnd(List *list, int number)
{
    Node *node = new(number, NULL);
    if (list->last)
    { // adaugare in list nevida
        list->last->next = node;
    }
    else
    { // adaugare in list vida
        list->first = node;
    }
    list->last = node;
}

void display(List *list)
{
    Node *current;
    for (current = list->first; current; current = current->next)
    {
        printf("%d ", current->number);
    }
    putchar('\n');
}

// elibereaza memoria ocupata de o list
void eliberare(List *list)
{
    Node *temporary, *current = list->first;
    while (current)
    {
        temporary = current->next;
        free(current);
        current = temporary;
    }
}

List *deleteItem(List *list, int number)
{
    Node *previous; // predecesor
    Node *current;  // element curent
    for (previous = NULL, current = list->first; current; previous = current, current = current->next)
    {
        if (current->number == number)
        {
            if (previous == NULL)
            { // deleteItem primul element din list
                list->first = list->first->next;
            }
            else
            { // deleteItem un element din interiorul listei
                previous->next = current->next;
            }

            free(current);

            return list;
        }
    }
    return list; // nu s-a gasit elementul in list
}

int main()
{
    List list;
    initialize(&list);
    addToTheEnd(&list, 108);
    addToTheEnd(&list, -1);
    addToTheEnd(&list, 49);

    deleteItem(&list, -1);

    display(&list);
    eliberare(&list);
    
    return 0;
}
