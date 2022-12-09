/*
    Aplicația 4.3: Să se scrie un program care primește în linia de comandă un nume de fișier, urmat de unul sau mai multe cuvinte.
    Programul va afișa liniile din fișier care conțin simultan toate cuvintele din linia de comandă, în orice ordine.
    Exemplu: ./cautare 1.txt ana ion         - va afișa toate liniile din fișierul 1.txt care conțin simultan ”ana” și ”ion”
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1

int checkLine(char *line, size_t numberOfNames, char **names);

int main(int counter, char **arguments)
{
    FILE *file;
    char line[1000], container[1000];

    if (!(file = fopen(*(arguments + 1), "rt")))
    {
        fprintf(stderr, "Error on opening the file");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, 1000, file) != NULL)
    {
        strcpy(container, line);
        if (checkLine(line, counter, arguments))
            puts(container);
    }

    return 0;
}

int checkLine(char *line, size_t numberOfNames, char **names)
{
    char **table;
    size_t lines = 1;

    table = (char **)calloc(sizeof(char *), lines);

    char *store = strtok(line, " ");
    while (store != NULL)
    {
        table = (char **)realloc(table, sizeof(char *) * lines);
        *(table + (lines - 1)) = (char *)realloc(*(table + (lines - 1)), sizeof(char) * (strlen(store) + 1));

        strcpy(table[lines - 1], store);
        if (table[lines - 1][strlen(store) - 1] == '\n')
            table[lines - 1][strlen(store) - 1] = '\0';
        else
            table[lines - 1][strlen(store)] = '\0';
            
        lines++;

        store = strtok(NULL, " ");
    }

    unsigned flag = 0;
    for (size_t i = 2; i < numberOfNames; i++)
        for (size_t j = 0; j < lines - 1; j++)
        {
            if (!strcmp(names[i], table[j]))
            {
                flag++;
                break;
            }
        }

    if (flag == numberOfNames - 2)
        return true;

    return false;
}