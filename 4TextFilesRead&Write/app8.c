/*
    Aplicația 4.8: Un fișier conține pe fiecare linie numele unui angajat (posibil mai multe cuvinte) și
    salariul său (număr real), separate prin virgulă. Să se scrie o aplicație care primește în linia de comandă un fișier sursă,
    unul destinație, un coeficient și două numere reprezentând un interval închis. Aplicația înmulțește toate salariile
    angajaților din intervalul dat cu coeficientul respectiv. Noua situație va fi scrisă în fișierul destinație.
    Exemplu de apel: ./actualizare angajati.txt nou.txt 1.25 0 1500               - se vor citi toți angajații din angajati.txt,
    iar la cei care au salariile în intervalul [0,1500] se vor înmulți acestea cu 1.25. Noua situație va fi scrisă în nou.txt.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int left;
    int right;
} Interval;

typedef struct
{
    double salary;
    char *name;
} Person;

typedef struct
{
    unsigned length;
    Person *person;
} DataBase;

DataBase *readFile(FILE *input, DataBase *dataBase, char *path);
void updateDataBase(FILE *output, DataBase *dataBase, char *path, Interval interval, double quotient);

int main(int counter, char *arguments[])
{
    FILE *input = NULL, *output = NULL;
    DataBase *dataBase = NULL;
    Interval interval = {0};

    dataBase = readFile(input, dataBase, arguments[1]);

    interval.left = atoi(arguments[3]);
    interval.right = atoi(arguments[4]);

    updateDataBase(output, dataBase, arguments[2], interval, atof(arguments[5]));

    free(dataBase);

    return 0;
}

DataBase *readFile(FILE *input, DataBase *dataBase, char *path)
{
    int count = 0;
    char character = 0, *line = (char *)calloc(sizeof(char), 1);

    dataBase = (DataBase *)calloc(sizeof(DataBase), 1);

    if (!dataBase)
    {
        fprintf(stderr, "Error on allocating the data base!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        dataBase->length = 1;
        dataBase->person = (Person *)calloc(sizeof(Person), 1);

        if (!dataBase->person)
        {
            fprintf(stderr, "Error on allocating the person field!\n");
            exit(EXIT_FAILURE);
        }
    }

    if (!(input = fopen(path, "rt")))
    {
        fprintf(stderr, "Error on opening the input!\n");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        character = fgetc(input);

        if (character != EOF && character != '\n')
        {
            *(line + count) = character;
            count++;
            line = (char *)realloc(line, sizeof(char) * (count + 1));
        }
        else if (character == '\n')
        {
            *(line + count) = '\0';
            count = 0;

            char *container = (char *)malloc(30);
            char *salary = (char *)malloc(30);

            container = strrchr(line, ' ');
            strcpy(salary, container);

            *(line + (container - line) + 1) = '\0';

            (dataBase->person + dataBase->length - 1)->name = (char *)malloc(sizeof(char) * (strlen(line) + 1));
            strcpy((dataBase->person + dataBase->length - 1)->name, line);

            (dataBase->person + dataBase->length - 1)->salary = atof(salary);

            dataBase->length++;
            dataBase->person = (Person *)realloc(dataBase->person, sizeof(Person) * (dataBase->length));

            line = (char *)calloc(sizeof(char), 1);

            free(salary); //*container points to *line memory zone, if i free *container then *line will be null
        }
        else if (character == EOF)
        {
            free(line);
            break;
        }
    }

    fclose(input);

    return dataBase;
}

void updateDataBase(FILE *output, DataBase *dataBase, char *path, Interval interval, double quotient)
{
    if (!(output = fopen(path, "wt")))
    {
        fprintf(stderr, "Error on opening the output file!\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < dataBase->length - 1; i++)
        if (((dataBase->person + i)->salary > interval.left) && ((dataBase->person + i)->salary < interval.right))
            (dataBase->person + i)->salary *= quotient, fprintf(output, "%s %0.2lf\n", (dataBase->person + i)->name, (dataBase->person + i)->salary);
        else
            fprintf(output, "%s %0.2lf\n", (dataBase->person + i)->name, (dataBase->person + i)->salary);

    fclose(output);
}