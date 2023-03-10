/*
    Aplicația 9.5: Să se scrie o funcție care primește două liste și returnează 1 dacă ele sunt egale,
    indiferent de ordinea și numărul elementelor, altfel returnează 0.
    Exemple: listele {1, 7, 3, 1, 3} și {7, 1, 3, 7} sunt egale. Listele {1,2} și {2} nu sunt egale.
*/

/*
    Aplicația 9.3: Să se scrie o funcție care primește ca parametri două liste și returnează o
    listă care reprezintă reuniunea elementelor lor, fiecare element apărând o singură dată,
    chiar dacă în listele originare el este duplicat.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int number;
    struct Node *next;
} Node;

Node *new(int number, Node *next);
Node *addElementToTheBeginning(int number, Node *node);
void displayElements(Node *node);
void freeMemory(Node *node);
size_t length(Node *node);
int compareLists(Node *node, Node *node2);
Node *sortList(Node *node);
Node *deleteDuplicates(Node *node);

int main()
{
    Node *node = new (1, new (7, new (3, new (1, new (3, NULL)))));
    Node *node2 = new (7, new (1, new (3, new (7, NULL))));

    Node *container = node, *container2 = node2;

    container = deleteDuplicates(container);
    container2 = deleteDuplicates(container2);

    container = sortList(container);
    container2 = sortList(container2);

    if (compareLists(container, container2))
    {
        displayElements(node);
        displayElements(node2);
    }
    else
        printf("Lists are not equals!\n");

    return 0;
}

Node *new(int number, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));

    if (!node)
    {
        printf("Error on allocating memory.\n");
        exit(EXIT_FAILURE);
    }

    node->number = number;
    node->next = next;

    return node;
}

Node *addElementToTheBeginning(int number, Node *node)
{
    return new (number, node);
}

void displayElements(Node *node)
{
    for (; node; node = node->next)
        printf("%i ", node->number);

    putchar('\n');
}

void freeMemory(Node *node)
{
    Node *next;

    while (node)
    {
        next = node->next;
        free(node);
        node = next;
    }
}

int exists(Node *node, Node *item)
{
    if (!node)
        return 0;

    while (node)
    {
        if (node->number == item->number)
            return 1;

        node = node->next;
    }

    return 0;
}

size_t length(Node *node)
{
    size_t counter = 0;
    struct Node *current = NULL;

    for (current = node; current; current = current->next)
        counter++;

    return counter;
}

int compareLists(Node *node, Node *node2)
{
    /*
        If line 110 is executed, then the complexity is O(1).

        If line 116 is executed, then the compelxity is between O(1) and O(n-1).

        If line 120 is executed, then the complexity is O(n);
    */

    if (length(node) != length(node2))
        return 0;

    Node *current = NULL, *current2 = NULL;

    for (current = node, current2 = node2; current; current = current->next, current2 = current2->next)
        if (current->number != current2->number)
            return 0;

    return 1;
}

Node *sortList(Node *node)
{
    Node *duplicate = node, *start = node;
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

    return start;
}

Node *deleteDuplicates(Node *node)
{
    Node *container = NULL;

    while (node)
    {
        if (!exists(container, node))
            container = addElementToTheBeginning(node->number, container);

        node = node->next;
    }

    return container;
}