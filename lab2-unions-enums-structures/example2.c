#include <stdio.h>

enum UnitateMasura
{
    UMBucata,
    UMKg
};

struct Produs
{
    char nume[20];
    double pret;
    enum UnitateMasura um; // unitate de masura
    union {
        int nBucati;
        double kg;
    } c;
};

void afisare(struct Produs *p)
{
    switch (p->um)
    {
    case UMBucata:
        printf("%d bucati\n", p->c.nBucati);
        break;
    case UMKg:
        printf("%g kg\n", p->c.kg);
        break;
    default:
        printf("unitate de masura invalida\n");
    }
}

void introducere(struct Produs *p)
{
    int um; // variabila auxiliara folosita pentru citire, deoarece nu se stie dimensiunea tipului enum
    printf("unitate de masura (0-nr. bucati, 1-kilograme): ");
    scanf("%d", &um);
    p->um = um; // copiere din variabila auxiliara in variabila de tip enum
    switch (p->um)
    {
    case UMBucata:
        printf("numar de bucati: ");
        scanf("%d", &p->c.nBucati);
        break;
    case UMKg:
        printf("greutate (kg): ");
        scanf("%lg", &p->c.kg);
        break;
    default:
        printf("unitate de masura invalida\n");
    }
}

int main()
{
    struct Produs p;
    introducere(&p);
    afisare(&p);
    return 0;
}
