#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printVector(int argc, char argv[10][20]);
void sort(int argc, char argv[10][20]);
void saveElements(int argc, char container[10][20], char *argv[]);

int main(int argc, char *argv[])
{
    char container[10][20];

    saveElements(argc, container, argv);

    printVector(argc, container);
    sort(argc, container);
    printVector(argc, container);

    return 0;
}

void printVector(int argc, char argv[10][20])
{
    for (int i = 1; i < argc; i++)
        printf("%s ", *(argv+i));

    putchar('\n');
}

void sort(int argc, char argv[10][20])
{
    char temp[20];

    for (unsigned i = 1; i < (argc); i++)
        for (unsigned j = 1; j < (argc - 1); j++)
        {
            if (atoi(*(argv + j)) > atoi(*(argv + j + 1)))
            {
                strcpy(temp, *(argv + j));
                strcpy(*(argv + j), *(argv + j + 1));
                strcpy(*(argv + j + 1), temp);
            }
        }
}

void saveElements(int argc, char container[10][20], char *argv[])
{
    for (int i = 0; i < argc; i++)
        strcpy(*(container + i), *(argv + i));
}