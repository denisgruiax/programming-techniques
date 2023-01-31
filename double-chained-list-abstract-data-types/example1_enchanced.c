#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Word
{
    char text[16];
    struct Word *previous;
    struct Word *next;
} Word;

typedef struct Phrase
{
    Word *first;
    Word *last;
} Phrase;

Word *new_word(const char *text);
void init_phrase(Phrase *phrase);
void add_word(Phrase *phrase, Word *word);
Word *search_word(Phrase *phrase, const char *text);
void delete_word(Phrase *phrase, Word *word);
void free_memory(Phrase *phrase);

int main(int argumentCounter, char *arguments[])
{
    Word *word;
    Phrase phrase;
    int operation = 0;
    char text[16];

    init_phrase(&phrase);

    do
    {
        printf("MENU\n");
        printf("1 - new phrase\n");
        printf("2 - display phrase\n");
        printf("3 - delete word\n");
        printf("4 - exit program\n");
        printf("option: ");

        scanf("%i", &operation);

        switch (operation)
        {
        case 1:
            free_memory(&phrase);

            for (;;)
            {
                scanf("%s", text);

                if (!strcmp(text, "."))
                    break;

                Word *word = new_word(text);

                add_word(&phrase, word);
            }

            break;

        case 2:
            for (word = phrase.first; word; word = word->next)
                printf("%s ", word->text);
            puts(".");

            break;

        case 3:
            printf("Insert word to delete: ");
            scanf("%s", text);

            word = search_word(&phrase, text);

            if (word)
                delete_word(&phrase, word);
            else
                printf("Word was not find in phrase.");

            break;

        case 4:
            free_memory(&phrase);
            printf("Stopping the program.");
            break;

        default:
            printf("Invalid option!");
            break;
        }

    printf("\n");

    } while (operation != 4);
}

Word *new_word(const char *text)
{
    Word *word = (Word *)malloc(sizeof(Word));

    if (!word)
    {
        fprintf(stderr, "Error on allocating new word!");
        exit(EXIT_FAILURE);
    }

    strcpy(word->text, text);

    return word;
}

void init_phrase(Phrase *phrase)
{
    phrase->first = phrase->last = NULL;
}

void add_word(Phrase *phrase, Word *word)
{
    word->previous = phrase->last;

    if (phrase->last)
        phrase->last->next = word;
    else
        phrase->first = word;

    phrase->last = word;

    word->next = NULL;
}

Word *search_word(Phrase *phrase, const char *text)
{
    Word *word;

    for (word = phrase->first; word; word = word->next)
        if (!strcmp(word->text, text))
            return word;

    return NULL;
}

void delete_word(Phrase *phrase, Word *word)
{
    if (word->previous)
        word->previous->next = word->next;
    else
        phrase->first = word->next;

    if (word->next)
        word->next->previous = word->previous;
    else
        phrase->last = word->previous;

    free(word);
}

void free_memory(Phrase *phrase)
{
    Word *word, *nextWord;

    for (word = phrase->first; word; word = nextWord)
    {
        nextWord = word->next;
        free(word);
    }

    init_phrase(phrase);
}