/*
    Se introduce un număr întreg n<10 și apoi n numere de tip float. 
    Să se folosească funcția qsort pentru a sorta aceste numere în mod crescător. 
    Se va introduce apoi un număr x de tip float. Folosind funcția bsearch, 
    să se determine dacă x există în vectorul sortat. Se pot consulta paginile de manual pentru funcțiile qsort și bsearch.
*/
#include <stdio.h>
#include <stdlib.h>

float *createVector(int size);
void sortVector(float *vector, int size, int (*cond)(const void *, const void *));
int compare(const void *element, const void *element2);
void readVector(float *vector, int size);
float *addElement(float *vector, int *size, const float *element, int (*compare)(const void *element1, const void *elemnt2));

int main(int argc, char *argv[])
{
    int size;

    printf("size = ");
    scanf("%d", &size);

    float *e1 = (calloc(1, sizeof(float)));
    *e1 = 25;
    float *vector = createVector(size);
    sortVector(vector, size, compare);
    readVector(vector, size);
    vector = addElement(vector, &size, e1, compare);
    readVector(vector, size);
}

float *createVector(int size)
{
    float *vector = (float *)malloc(sizeof(float) * size);

    for (float *i = vector; i < &vector[size]; i++)
        scanf("%f", i);

    return vector;
}

int compare(const void *element, const void *element2)
{
    const float *x, *y;
    x = (const float *)element;
    y = (const float *)element2;

    return (*x - *y);
}

void sortVector(float *vector, int size, int (*cond)(const void *, const void *))
{
    qsort(vector, size, sizeof(float), cond);
}

void readVector(float *vector, int size)
{
    for (float *i = vector; i < &vector[size]; i++)
        printf("%0.2f ", *i);
}

float *addElement(float *vector, int *size, const float *element, int (*compare)(const void *element1, const void *elemnt2))
{
    float *item = bsearch(element, vector, *size, sizeof(float), compare);

    if (!item)
    {
        puts("The element had not found, adding element...");
        (*size)++;
        vector = realloc(vector, sizeof(float) * (*size));
        vector[*size - 1] = *element;
        sortVector(vector, *size, compare);
    }
    else
    {
        puts("The element is already added.");
    }

    return vector;
}
