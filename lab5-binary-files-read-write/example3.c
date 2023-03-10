/*
    Exemplul 3 : Să se modifice exemplul de mai sus, astfel încât în baza de date fiecare nume de produs să 
    ocupe minimul necesar de memorie.Fiecare nume va putea avea maxim 1000 de caractere :
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    typedef struct
{
    char *nume;
    float pret;
} Produs;

Produs produse[1000];
int nProduse;

void adaugare()
{
    Produs p;
    char nume[1000];

    printf("nume: ");
    fgets(nume, 1000, stdin);
    nume[strcspn(nume, "\r\n")] = '\0';
    
    if ((p.nume = (char *)malloc((strlen(nume) + 1) * sizeof(char))) == NULL)
    {
        printf("memorie insuficienta");
        exit(EXIT_FAILURE);
    }

    strcpy(p.nume, nume);
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
    int i;
    unsigned short nNume; // numarul de caractere dintr-un nume de produs

    if ((fis = fopen("produse.dat", "wb")) == NULL)
    {
        printf("nu se poate deschide fisierul\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < nProduse; i++)
    {
        nNume = (unsigned short)strlen(produse[i].nume);
        fwrite(&nNume, sizeof(unsigned short), 1, fis);    // scriere lungime sir in fisier
        fwrite(produse[i].nume, sizeof(char), nNume, fis); // scriere sir, fara terminator
        fwrite(&produse[i].pret, sizeof(float), 1, fis);
    }

    fclose(fis);
}

void eliberare()
{
    int i;
    for (i = 0; i < nProduse; i++)
        free(produse[i].nume);
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
            eliberare();
            break;
        default:
            printf("optiune invalida\n");
        }
    } while (optiune != 3);
    return 0;
}
