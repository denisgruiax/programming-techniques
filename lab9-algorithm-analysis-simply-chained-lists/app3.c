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
Node *unionTwoList(Node *node1, Node *node2);

int main()
{
    Node *node = new (1, new (2, new (4, NULL)));
    Node *node2 = new (3, new (2, new (5, NULL)));

    displayElements(node);
    displayElements(node2);

    Node *set = unionTwoList(node, node2);

    displayElements(set);

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

Node *unionTwoList(Node *node1, Node *node2)
{
    Node *container = (Node *)malloc(sizeof(Node));

    container = NULL;

    while (node1)
    {
        if (!exists(container, node1))
            container = addElementToTheBeginning(node1->number, container);

        node1 = node1->next;
    }

    while (node2)
    {
        if (!exists(container, node2))
            container = addElementToTheBeginning(node2->number, container);

        node2 = node2->next;
    }

    return container;
}