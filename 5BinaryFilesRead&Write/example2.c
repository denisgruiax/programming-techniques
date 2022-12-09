/*
    Aplicația 5.1: Modificați exemplul anterior, astfel încât să se scrie la început de fișier numărul de produse din baza de date.


    Valoriile marcate la final in float ale pretului au fost cerute de cerinta sa fie scrise la inceput de memorie si nu la final.
    Am modificat direct pe exemplul.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    float pret;
    char nume[28];
} Produs;

Produs produse[1000];
int nProduse;

void adaugare()
{
    Produs p;
    printf("nume: ");
    fgets(p.nume, 28, stdin);
    p.nume[strcspn(p.nume, "\r\n")] = '\0';
    printf("pret: ");
    scanf("%g", &p.pret);
    produse[nProduse] = p;
    nProduse++;
}

void afisare()
{
    int i;
    for (i = 0; i < nProduse; i++)
    {
        printf("%s: %g\n", produse[i].nume, produse[i].pret);
    }
}

void scriere()
{
    FILE *fis;

    if ((fis = fopen("example2.dat", "wb")) == NULL)
    {
        printf("nu se poate deschide fisierul\n");
        exit(EXIT_FAILURE);
    }
    fwrite(produse, sizeof(Produs), nProduse, fis);
    fclose(fis);
}

int main()
{
    int optiune;
    do
    {
        printf("optiune: ");
        scanf("%d", &optiune);
        getchar();
        switch (optiune)
        {
        case 1:
            adaugare();
            break;
        case 2:
            afisare();
            break;
        case 3:
            scriere();
            break;
        default:
            printf("optiune invalida\n");
        }
    } while (optiune != 3);
    return 0;
}
