/*
    Aplicația 2.6: Să se codifice următoarele informații despre un medicament, astfel încât ele să ocupe 
    în total un singur octet. Să se scrie un program care să citească datele unui medicament și ulterior să le afișeze.
    gradul de periculozitate: scăzută, medie, mare
    dacă se eliberează doar pe bază de rețetă: da, nu
    vârsta minimă de administrare: 1...18 ani inclusiv
*/
#include <stdio.h>
#include <stddef.h>

typedef struct
{
    unsigned char minAge : 5;
    unsigned char dangerous : 2;
    unsigned char release : 1;
    
} Medicament;

void writeStructure(Medicament *medicament);
void readStructure(Medicament medicament);

int main(int argc, char *argv[])
{
    Medicament medicament;

    writeStructure(&medicament);
    printf("\nsizeof: %lu\n", sizeof(medicament));
    readStructure(medicament);
    return 0;
}

void writeStructure(Medicament *medicament)
{
    unsigned char temporary;

    printf("dangerous: ");
    scanf("%hhu", &temporary);
    medicament->dangerous = temporary;

    printf("release: ");
    scanf("%hhu", &temporary);
    medicament->release = temporary;

    printf("min age: ");
    scanf("%hhu", &temporary);
    medicament->minAge = temporary;
}

void readStructure(Medicament medicament)
{
    printf("\ndangerous: %u\n", medicament.dangerous);
    printf("release: %u\n", medicament.release);
    printf("min age: %u\n", medicament.minAge);
}