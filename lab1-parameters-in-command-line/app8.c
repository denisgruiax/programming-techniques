/*
    Aplicația 1.8: Să se scrie un program denumit criptare, care criptează/decriptează un text primit în linia de comandă. 
    Programul va fi apelat în felul următor:       ./criptare operatie cheie cuvant1 cuvant2 ...
    Operația poate fi enc pentru criptare sau dec decriptare. Cheia este un număr întreg. 
    Algoritmul de criptare este următorul: pentru fiecare literă din cuvinte se consideră codul său ASCII, 
    la care se adună cheia specificată, rezultând un nou cod ASCII, cel al literei criptate. 
    Adunarea este circulară, adică ‘z’ incrementat cu 1 devine ‘a’. 
    Decriptarea este inversă: din cuvintele criptate se scade circular cheia specificată. 
    Literele mari se transformă la început în litere mici.
    Exemple:
    ./criptare enc 1 zaraza    ->    absbab
    ./criptare dec 1 bcfdfebs    ->    abecedar
    ./criptare enc 10 vine VINE primavara PRImaVAra    ->    fsxo fsxo zbswkfkbk zbswkfkbk
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void start(int counter, char *arguments[], char *key);
void encryption(int counter, char *arguments[], char *key);
void decryption(int counter, char *arguments[], char *key);
char addition(char character, char *key);
char subtraction(char character, char *key);
void printMatrix(int counter, char *arguments[]);

int main(int counter, char *arguments[])
{
    start(counter, arguments, arguments[2]);
}

void start(int counter, char *arguments[], char *key)
{
    if (!strcmp("enc", arguments[1]))
    {
        encryption(counter, arguments, arguments[2]);
        printMatrix(counter, arguments);
    }
    else if (!strcmp("dec", arguments[1]))
    {
        decryption(counter, arguments, arguments[2]);
        printMatrix(counter, arguments);
    }
    else
    {
        printf("Bad option...\n");
    }
}

void encryption(int counter, char *arguments[], char *key)
{
    for (int count = 3; count < counter; count++)
        for (int j = 0; j < strlen(arguments[count]); j++)
            arguments[count][j] = addition(arguments[count][j], key);
}

void decryption(int counter, char *arguments[], char *key)
{
    for (int count = 3; count < counter; count++)
        for (int j = 0; j < strlen(arguments[count]); j++)
            arguments[count][j] = subtraction(arguments[count][j], key);
}

char addition(char character, char *key)
{
    int code = tolower(character);
    int inc = atoi(key);

    while (inc--)
    {
        code++;

        if (code == 123)
            code = 97;
    }

    return (char)code;
}

char subtraction(char character, char *key)
{
    int code = tolower(character);
    int inc = atoi(key);

    while (inc--)
    {
        code--;

        if (code == 96)
            code = 122;
    }

    return (char)code;
}

void printMatrix(int counter, char *arguments[])
{
    for (unsigned count = 3; count < counter; count++)
        printf("%s ", arguments[count]);

    putchar('\n');
}