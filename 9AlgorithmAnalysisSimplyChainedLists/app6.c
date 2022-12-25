/*
    Aplicația 9.6: Să se scrie o funcție care primește ca parametri o listă (posibil vidă) de elemente sortate și un element.
    Funcția va insera în listă noul element, astfel încât lista să rămână sortată. Folosind aceasta funcție, să se scrie o
    funcție de sortare a unei liste, care primește ca parametru o listă nesortată și returnează una sortată.
    Programul nu va folosi niciun vector.
*/

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
Node *insertElementAndSortList(Node *node, int number);

int main()
{
    Node *node = new (1, new (7, new (3, new (1, new (3, NULL)))));

    node = insertElementAndSortList(node, 4);

    displayElements(node);

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

Node *insertElementAndSortList(Node *node, int number)
{
    Node *duplicate = NULL, *start = NULL;
    int data = 0;

    node = addElementToTheBeginning(4, node);

    start = node;
    duplicate = node;

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