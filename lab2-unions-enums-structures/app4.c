/*
    Aplicația 2.4: Folosind câmpuri pe biți, definiţi o structură pentru memorarea următoarelor informaţii despre animale:
    numărul de picioare: număr întreg, minim 0 (ex. şarpe), maxim 1000 (ex. miriapod)
    greutatea în kg: număr real
    periculos pentru om: da/nu
    abrevierea ştiinţifică a speciei: şir de maxim 8 caractere
    vârsta maximă în ani: număr întreg, minim 0, maxim 2000
    Unde este posibil, codificaţi informaţiile prin numere întregi de dimensiune cât mai mică, spre exemplu “da”=1, “nu”=0. 
    Definiţi structura în aşa fel încât să ocupe spaţiul minim de memorie posibil. Afişaţi spaţiul de memorie ocupat, 
    folosind operatorul sizeof. Folosind structura definită, citiţi de la tastatură informaţii despre un animal, 
    iar pe urmă afişaţi-le pe ecran.
*/

#include <stdio.h>

typedef struct
{
    unsigned legs : 10;
    unsigned char dangerous : 1;
    unsigned maxAge : 11;
    float kg;
    char abr[8];
} Animals;

void writeStructure(Animals *animal);
void readStructure(Animals *animal);

int main(int argc, char *argv[])
{
    Animals animal;
    writeStructure(&animal);
    printf("\nsizeof real: %lu\n", sizeof(animal));
    readStructure(&animal);
    
    return 0;
}

void writeStructure(Animals *animal)
{
    unsigned size;
    printf("legs: ");
    scanf("%u", &size);
    animal->legs = size;

    printf("dangerous: ");
    scanf("%u", &size);
    animal->dangerous = size;

    printf("max age: ");
    scanf("%u", &size);
    animal->maxAge = size;

    printf("kg: ");
    scanf("%f", &animal->kg);

    printf("abreviation: ");
    scanf("%8s", &animal->abr);
}
void readStructure(Animals *animal)
{
    printf("\nsizeof: %lu <- pointer size\n", sizeof(animal));
    printf("legs: %u\n", animal->legs);
    printf("dangerous: %u\n", animal->dangerous);
    printf("age: %u\n", animal->maxAge);
    printf("kg: %0.2f\n", animal->kg);
    printf("abr: %s\n", animal->abr);
}