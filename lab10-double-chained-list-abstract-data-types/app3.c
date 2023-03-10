/*
    Aplicația 10.3: Să se adauge la TDA-ul LISTAD operația de inserare cu 3 parametri: lista de inserat (lista),
    elementul înainte de care se face inserarea (pos) și elementul de inserat (e). Dacă pos!=NULL,
    atunci e se va insera înainte de pos. Dacă pos==NULL, atunci e se va insera la sfârșitului listei.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word
{
    char text[16];
    struct Word *previous;
    struct Word *next;
} Word;

Word *new_word(const char *text)
{
    Word *word = (Word *)malloc(sizeof(Word));
    if (!word)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }
    strcpy(word->text, text);
    return word;
}

#define LIST_AD_NUME Phrase  // numele TDA
#define LIST_AD_ELEMENT Word // tipul unui element din lista

#include "app3.h"

Word *Phrase_search(Phrase *phrase, const char *text)
{
    Word *word;
    for (word = phrase->first; word; word = word->next)
    {
        if (!strcmp(word->text, text))
            return word;
    }
    return NULL;
}

int main()
{
    Phrase phrase;
    int op; // optiune
    char text[16];
    Word *word, *element, *position;

    Phrase_initialize(&phrase);
    do
    {
        printf("1 - propozitie noua\n");
        printf("2 - afisare\n");
        printf("3 - stergere cuvant\n");
        printf("4 - adauaga cuvant pozitie\n");
        printf("5 - iesire\n");
        printf("optiune: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            Phrase_freeMemory(&phrase);
            for (;;)
            {
                scanf("%s", text);
                if (!strcmp(text, "."))
                    break;
                Word *word = new_word(text);
                Phrase_add(&phrase, word);
            }
            break;
        case 2:
            for (word = phrase.first; word; word = word->next)
                printf("%s ", word->text);
            printf(".\n");
            break;
        case 3:
            printf("cuvant de sters:");
            scanf("%s", text);
            word = Phrase_search(&phrase, text);
            if (word)
            {
                Phrase_delete(&phrase, word);
            }
            else
            {
                printf("cuvantul \"%s\" nu se gaseste in propozitie\n", text);
            }
            break;
        case 4:
            printf("cuvant de adaugat: ");
            scanf("%s", text);
            element = new_word(text);

            printf("position: ");
            scanf("%s", text);
            position = new_word(text);

            Phrase_addElementBeforePosition(&phrase, position, element);
            break;

        case 5:
            Phrase_freeMemory(&phrase);
            break;
        default:
            printf("optiune invalida");
        }
    } while (op != 5);
    return 0;
}