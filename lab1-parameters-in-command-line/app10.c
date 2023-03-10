/*
    Aplicația 1.10: Un program primește în linia de comandă o serie de opțiuni și de cuvinte, mixate între ele.
    Opțiunile specifică operații care se execută asupra cuvintelor. Opțiunile încep cu - (minus) și pot fi:
    u-transformă toate literele cuvintelor în majuscule;
    f-transformă prima literă în majusculă și următoarele în minuscule; r-inversează literele din cuvinte.
    După fiecare cuvânt se resetează toate opțiunile anterioare.
    Să se afișeze cuvintele primite în linia de comandă cu transformările aplicate.
    Exemplu: ./procesare -f mAria -r -u abac        va afișa: Maria CABA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    unsigned opt1, opt2, opt3;
} Options;

char *g_text;

void stringToUpper(char *word);
void setFirstCharToUpperAndTheRestToLower(char *word);
void reverseString(char *word);
char *addWord(char *string, char *word);
void processing(int counter, char *arguments[]);

int main(int counter, char *arguments[])
{
    processing(counter, arguments);

    puts(g_text);

    free(g_text);

    return 0;
}

void stringToUpper(char *word)
{
    while (*word)
    {
        *word = toupper(*word);
        word++;
    }
}

void setFirstCharToUpperAndTheRestToLower(char *word)
{
    *word = toupper(*word);

    while (*word != '\0')
    {
        word++;
        *word = tolower(*word);
    }
}

void reverseString(char *string)
{
    unsigned char store;
    unsigned len = strlen((const char *)string);

    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        store = string[i];
        string[i] = string[j];
        string[j] = store;
    }
}

char *addWord(char *string, char *word)
{
    if (!string)
    {
        string = (char *)malloc(sizeof(word) + 1);

        if (!string)
        {
            exit(EXIT_FAILURE);
            free(string);
        }

        strcat(string, word);
    }
    else
    {
        string = (char *)realloc(string, sizeof(string) + sizeof(word) + 1);

        if (!string)
        {
            exit(EXIT_FAILURE);
            free(string);
        }

        strcat(string, " ");
        strcat(string, word);
    }

    return string;
}

void processing(int counter, char *arguments[])
{
    Options options = {0};
    char *store;

    for (unsigned i = 1; i < counter; i++)
    {
        if (strcmp(arguments[i], "-u") == 0)
            options.opt1 = 1;

        else if (strcmp(arguments[i], "-f") == 0)
            options.opt2 = 1;

        else if (strcmp(arguments[i], "-r") == 0)
            options.opt3 = 1;
        else
        {
            store = (char *)malloc(sizeof(arguments[i]));
            strcpy(store, arguments[i]);

            if (options.opt1)
            {
                stringToUpper(store);
                options.opt1 = 0;
            }

            if (options.opt2)
            {
                setFirstCharToUpperAndTheRestToLower(store);
                options.opt2 = 0;
            }

            if (options.opt3)
            {
                reverseString(store);
                options.opt3 = 0;
            }

            g_text = addWord(g_text, store);
            free(store);
        }
    }
}