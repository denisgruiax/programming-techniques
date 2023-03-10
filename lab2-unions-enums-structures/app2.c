/*
    Aplicația 2.2: Folosind struct și union, definiți o structură de date care să poată memora următoarele informații despre viețuitoare:
    tipul (poate fi: mamifer, insectă, pește, pasăre)
    durata medie de viață în ani
    dacă e mamifer: perioada de gestație, numărul mediu de pui pe care îi naște
*/

#include <stdio.h>

typedef enum
{
    MAMMALIAN,
    INSECT,
    FISH,
    BIRD
} Type;

char *names[20] = {"Mammalian", "Insect", "Fish", "Bird"};

typedef struct
{
    Type type;
    unsigned averageLifeTime;

    union {
        struct
        {
            unsigned gestationPeriod; //months
            unsigned averageNumberOfBabies;
        } M;

        struct
        {
            unsigned char canFly;        // 0 | 1
            unsigned char isItDangerous; // 0 | 1
            int numberOfLegs;
        } I;

        struct
        {
            unsigned char waterType; // 0 | 1
            unsigned maximumDepth;   // meters
            unsigned maxSpeed;       //km/h
        } F;

        struct
        {
            unsigned maxSpan;     //in cm
            unsigned maxAltitude; //km
            unsigned maxSpeed;    // km/h
        } B;
    } U;

} Creatures;

void readStructure(Creatures *creature);
void printStructure(Creatures *creature);

int main(int argc, char *argv[])
{
    Creatures creature;
    readStructure(&creature);
    printStructure(&creature);

    return 0;
}

void readStructure(Creatures *creature)
{
    unsigned char temp;

    printf("Type (0 - M, 1-I, 2-F, 3-B): ");
    scanf("%hhu", &temp);
    creature->type = temp;

    printf("Average life time (Years): ");
    scanf("%u", &creature->averageLifeTime);

    switch (creature->type)
    {
    case 0:
        printf("gestation period: ");
        scanf("%u", &(creature->U.M.gestationPeriod));

        printf("Average number of babies: ");
        scanf("%u", &(creature->U.M.averageNumberOfBabies));

        break;
    case 1:
        printf("Can it fly?: ");
        scanf("%hhu", &(creature->U.I.canFly));

        printf("Is it dangerous?: ");
        scanf("%hhu", &(creature->U.I.isItDangerous));

        printf("Number of legs: ");
        scanf("%u", &(creature->U.I.numberOfLegs));

        break;
    case 2:
        printf("Water type: ");
        scanf("%hhu", &(creature->U.F.waterType));

        printf("Max depth: ");
        scanf("%u", &(creature->U.F.maximumDepth));

        printf("Max speed: ");
        scanf("%u", &(creature->U.F.maxSpeed));
        break;
    case 3:
        printf("Max span: ");
        scanf("%u", &(creature->U.B.maxSpan));

        printf("Max altitude: ");
        scanf("%u", &(creature->U.B.maxAltitude));

        printf("Max speed: ");
        scanf("%u", &(creature->U.B.maxSpeed));
        break;

    default:
        printf("Bad option.\n");
        break;
    }
}
void printStructure(Creatures *creature)
{
    printf("\nType: %s\n", names[creature->type]);
    printf("Average lifetime: %u\n", creature->averageLifeTime);

    switch (creature->type)
    {
    case 0:
        printf("Gestation: %u\n", creature->U.M.gestationPeriod);
        printf("Average number of babies: %u\n", creature->U.M.averageNumberOfBabies);
        break;

    case 1:
        printf("Can fly: %s\n", (creature->U.I.canFly) ? "Yes" : "No");
        printf("Dangerous: %s\n", creature->U.I.isItDangerous ? "yes" : "No");
        printf("Legs: %u\n", creature->U.I.numberOfLegs);
        break;

    case 2:
        printf("Water type: %s\n", creature->U.F.waterType ? "Sweet" : "Salted");
        printf("Depth: %u\n", creature->U.F.maximumDepth);
        printf("Speed: %u\n", creature->U.F.maxSpeed);
        break;

    case 3:
        printf("Span: %u\n", creature->U.B.maxSpan); // float point like 1.2m or unsigned like 120cm
        printf("Altitude: %u\n", creature->U.B.maxAltitude);
        printf("Speed: %u\n", creature->U.B.maxSpeed);
        break;

    default:printf("Bad option.");
        break;
    }
}
