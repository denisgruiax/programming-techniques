#include <stdio.h>

void remakeVector(int *vector, unsigned *size, int (*cond)(int));
void deleteVector(int *vector, unsigned *size, unsigned *index);
int isNegative(int number);
void readVector(int *vector, unsigned size);

int main(int argc, char *argv[])
{
    unsigned size = 7;
    int vector[7] = {-6, 4, 1, -20, -5, 18, -37};

    remakeVector(vector, &size, isNegative);
    readVector(vector, size);
}

void remakeVector(int *vector, unsigned *size, int (*cond)(int))
{
    for (unsigned i = 0; i < *size; i++)
        if (cond(vector[i]))
            deleteVector(vector, size, &i);
}

void deleteVector(int *vector, unsigned *size, unsigned *index)
{
    for (unsigned j = *index; j < *size; j++)
        vector[j] = vector[j + 1];

    (*size)--, (*index)--;
}

int isNegative(int number)
{
    if (number < 0)
        return 1;

    return 0;
}

void readVector(int *vector, unsigned size)
{
    for (unsigned i = 0; i < size; i++)
        printf("%d ", vector[i]);
}