/*
    Aplicația 4.5: Să se contorizeze de câte ori apare într-un fișier fiecare cuvânt și să se afișeze.
    Nu se va face distincție între literele mari și mici.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wordSize 30

char **removeSameWord(char **wordList, unsigned *length);

int main()
{
    FILE *file = NULL;
    char word[wordSize] = {0}, **wordList = NULL, **container = NULL;
    unsigned lengthWordList = 0;

    if (!(file = fopen("app5.txt", "rt")))
    {
        fprintf(stderr, "Error on opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%s", word) == 1)
    {
        lengthWordList++;

        wordList = (char **)realloc(wordList, sizeof(char *) * lengthWordList);
        *(wordList + (lengthWordList - 1)) = (char *)realloc(*(wordList + (lengthWordList - 1)), sizeof(char) * wordSize);

        if (strlen(word) > 2)
            strcpy(*(wordList + (lengthWordList - 1)), word);
    }

    unsigned newLength = lengthWordList;
    container = removeSameWord(wordList, &newLength);
    int *occurence = (int *)calloc(sizeof(int), newLength);

    for (size_t i = 0; i < newLength; i++)
        for (size_t j = 0; j < lengthWordList; j++)
            if (!strcmp(*(container + i), *(wordList + j)))
                occurence[i]++;

    for (size_t i = 0; i < newLength; i++)
        printf("%s -> %i\n", container[i], occurence[i]);

    fclose(file);

    return 0;
}

char **removeSameWord(char **wordList, unsigned *length)
{
    char **container = NULL;

    container = (char **)realloc(container, sizeof(char *) * *length);
    for (size_t i = 0; i < *length; i++)
    {
        *(container + i) = (char *)realloc(*(container + i), sizeof(char) * wordSize);
        strcpy(*(container + i), *(wordList + i));
    }

    for (size_t i = 0; i < *length; i++)
    {
        for (size_t j = 0; j < *length; j++)
        {
            if (i != j && !(strcmp(*(container + i), *(container + j))))
            {
                for (size_t k = j; k < *length - 1; k++)
                    strcpy(*(container + k), *(container + (k + 1)));

                (*length)--;
                container = (char **)realloc(container, sizeof(char *) * *length);
            }
        }
    }

    return container;
}