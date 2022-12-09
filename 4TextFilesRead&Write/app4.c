/*
    Aplicația 4.4: Citind caracter cu caracter dintr-un fișier, să se contorizeze de câte ori apare fiecare literă din alfabet
    și să se afișeze. Nu se va face distincție între literele mari și mici.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define wordSize 30

void removeSameWord(char **wordList, unsigned length);

int main()
{
    FILE *file = NULL;
    char character = 0;
    int alphabet[26] = {0};

    if (!(file = fopen("app4.txt", "rt")))
    {
        fprintf(stderr, "Error on opening the file.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%c", &character) == 1)
    {
        if (isalpha(character))
        {
            character = toupper(character);
            alphabet[character - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        printf("%c -> %i\n", ((char) i + 'A'), alphabet[i]);
    }

    fclose(file);

    return 0;
}