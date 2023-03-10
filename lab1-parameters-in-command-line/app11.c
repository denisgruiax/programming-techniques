/*
    Aplicația 1.11: Un program primește în linia de comandă ca prim argument un cod de operație și pe urmă o serie de cuvinte. 
    Codul poate fi: 
        0-afișează numărul total de litere din toate cuvintele: 
        1-afișează fiecare literă de câte ori apare în toate cuvintele.
    Exemplu: ./statistica 0 ion merge la film          va afișa: 14
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char character;
    unsigned appearances;
} Table;

unsigned tableSize, key;
Table *table;

void processing(int counter, char *arguments[]);
unsigned lengthOfMatrix(int counter, char *arguments[]);
void fillTable(int counter, char *arguments[]);
unsigned checker(Table *table, char toTry);

int main(int counter, char *arguments[])
{
    processing(counter, arguments);
}

void processing(int counter, char *arguments[])
{
    if (atoi(arguments[1]) == 0)
    {
        printf("%u\n", lengthOfMatrix(counter, arguments));
    }

    if(atoi(arguments[1]) == 1)
    {
        fillTable(counter, arguments);

        printf("Char\tApps\n");
        for (unsigned i = 0; i < tableSize; i++)
        {
            printf("%c\t%u\n", table[i].character, table[i].appearances);
        }
    }  
}


unsigned lengthOfMatrix(int counter, char *arguments[])
{
    unsigned length = 0;

    for (unsigned i = 2; i < counter; i++)
    {
        length += strlen(arguments[i]);
    }

    return length;
}

void fillTable(int counter, char *arguments[])
{
    for (unsigned i = 2; i < counter; i++)
    {
        for (unsigned j = 0; j < strlen(arguments[i]); j++)
        {
            if (!checker(table, arguments[i][j]))
            {
                tableSize++;
                if (!(table = realloc(table, sizeof(table) * tableSize)))
                {
                    free(table);
                    exit(EXIT_FAILURE);
                }

                table[tableSize - 1].character = arguments[i][j];
                table[tableSize - 1].appearances = 1;
            }
            else
            {
                table[key].appearances++;
            }
        }
    }
}

unsigned checker(Table *table, char toCheck)
{
    for (unsigned i = 0; i < tableSize; i++)
        if (table[i].character == toCheck)
        {
            key = i;
            return 1;
        }

    return 0;
}