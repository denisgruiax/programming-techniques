/*
    Aplicația 8.7: Să se scrie o funcție int comune(int nVec,...) care primește un număr de vectori cu valori
    de tip int și vectorii propriu-ziși. Fiecare vector se dă prin 2 argumente: un pointer la elementele sale
    și dimensiunea. Funcția va returna numărul de elemente comune care se regăsesc în toți vectorii.
    Exemplu: comune(3,v1,2,v2,3,v3,3)		=> returnează 2 pentru v1={5,8}, v2={8,3,5}, v3={5,0,8}
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int checkRow(int *row, int size, int element)
{
    for (size_t i = 0; i < size; i++)
        if (*(row + i) == element)
            return TRUE;

    return FALSE;
}

int getIndexOfSmallestVector(int *vector, int size)
{
    int min = *vector, index = 0;

    for (size_t i = 1; i < size; i++)
        if (min > *(vector + i))
            index = i;

    return index;
}

int numberOfCommonElements(int size, ...)
{
    int **matrix = NULL, *sizeOfVectors = NULL;

    sizeOfVectors = (int *)calloc(sizeof(int), size);

    matrix = (int **)calloc(sizeof(int *), size);

    va_list variableArguments;         // pointer la lista de argumente variabile (varargs)
    va_start(variableArguments, size); // variableArguments trebuie initializat cu ultimul argument fix al functiei

    for (size_t i = 0; i < size; i++)
    {
        *(matrix + i) = va_arg(variableArguments, int *);
        *(sizeOfVectors + i) = va_arg(variableArguments, int);
    }

    va_end(variableArguments); // dupa folosirea argumentelor variabile, trebuie apelat va_end

    int commonElements = 0, flag = 0;

    int index = getIndexOfSmallestVector(sizeOfVectors, size);

    for (size_t i = 0; i < *(sizeOfVectors + index); i++)
    {
        for (size_t j = 0; j < size; j++)
            if (j != index)
                
                {
                    printf("%lu %i %i\n", j, *(sizeOfVectors + j), *(*(matrix + index) + i));
                   
                    if (checkRow(*(matrix + j), *(sizeOfVectors + j), *(*(matrix + index) + i)))
                        flag++;
                }

        if (flag == size-1)
            commonElements++;

        flag = 0;
    }
    
    return commonElements;
}

int main()
{
    int v1[] = {5, 8}, v2[] = {8, 3, 5}, v3[] = {5, 0, 8};

    printf("result = %i\n", numberOfCommonElements(3, v1, 2, v2, 3, v3, 3));

    return 0;
}