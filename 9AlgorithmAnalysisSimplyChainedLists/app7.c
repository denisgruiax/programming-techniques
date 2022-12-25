/*
    Aplicația 9.7 : Pentru implementarea listei care memorează ultimul element, să se scrie o
    funcție care primește două liste sortate și returnează lista sortată care conține toate elementele lor.
    Pentru lista rezultată se va folosi doar operația de adăugare la sfârșit de listă.Exemplu : {1, 2, 7, 8} și { 2, 9 } ->
    {1, 2, 2, 7, 8, 9 }
*/

#include <stdio.h>
#include <stdlib.h>

// un element al listei
typedef struct Node
{
    int number;        // informatia utila
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
    Node *first; // primul element din list
    Node *last;  // ultimul element din list
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
    list->first = new (number, first);
    if (!first)
    { // list initiala vida - trebuie setat si last pe elementul adaugat
        list->last = list->first;
    }
}

// adauga un element la sfarsitul listei
void addToTheEnd(List *list, int number)
{
    Node *node = new (number, NULL);

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

List sortList(List *list)
{

    Node *node = list->first, *duplicate = node, *start = node;
    int data;

    // 1->3->2->4->NULL
    // 1->2->3->4->NULL
    for (duplicate = start; duplicate; duplicate = duplicate->next)
        for (node = start; node->next; node = node->next)
        {
            if ((node->number) > ((node->next->number)))
            {
                data = node->number;
                node->number = node->next->number;
                node->next->number = data;
            }
        }

    list->first = start;

    return *list;
}

List merge(List *list, List *list2)
{
    Node *start = list2->first;

    for (; start; start = start->next)
        addToTheEnd(list, start->number);

    return sortList(list);
}

int main()
{
    List list, list2;
    initialize(&list);
    initialize(&list2);

    addToTheEnd(&list, 1);
    addToTheEnd(&list, 2);
    addToTheEnd(&list, 7);
    addToTheEnd(&list, 8);

    addToTheEnd(&list2, 2);
    addToTheEnd(&list2, 9);

    merge(&list, &list2);
    display(&list);

    eliberare(&list);
    eliberare(&list2);

    return 0;
}