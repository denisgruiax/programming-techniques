/*
    Aplicația 5.4: Să se modifice exemplul 4, astfel încât la începutul fișierului să fie scris numărul de produse.
    Citirea va fi modificată pentru a folosi această informație, în loc de a se testa sfârșitul de fișier.
*/

/*
    Exemplul 4 : Să se completeze exemplul anterior, astfel încât la execuția programului prima oară
    să se încarce baza de date de pe disc.Dacă încă nu există o bază de date, programul va funcționa normal,
    fără să se emită un mesaj de eroare.
*/

// au fost redate doar partile din program care au fost modificate sau adaugate

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

void scriere()
{
    FILE *fis;
    int i;
    unsigned short nNume; // numarul de caractere dintr-un nume de produs

    if ((fis = fopen("app4.dat", "wb")) == NULL)
    {
        printf("nu se poate deschide fisierul\n");
        exit(EXIT_FAILURE);
    }

    fwrite(&nProduse, sizeof(int), 1, fis);

    for (i = 0; i < nProduse; i++)
    {
        nNume = (unsigned short)strlen(produse[i].nume);
        fwrite(&nNume, sizeof(unsigned short), 1, fis);    // scriere lungime sir in fisier
        fwrite(produse[i].nume, sizeof(char), nNume, fis); // scriere sir, fara terminator
        fwrite(&produse[i].pret, sizeof(float), 1, fis);
    }

    fclose(fis);
}

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

void eliberare()
{
    int i;
    for (i = 0; i < nProduse; i++)
        free(produse[i].nume);
}

void citire()
{
    FILE *fis;
    unsigned short nNume;

    if ((fis = fopen("app4.dat", "rb")) == NULL)
        return; // iesire din functie in caz cu nu exista baza de date
    // deoarece in fisier nu exista numarul de elemente
    // se foloseste o bucla infinita, care continua atata timp cat se mai pot citi noi elemente

    // modificare
    int numarProduse = 0;
    fread(&numarProduse, sizeof(int), 1, fis);

    for (size_t i = 0; i < numarProduse; i++)
    {
        // se incearca citirea unui nou produs, care incepe cu dimensiunea numelui
        // daca fread nu reuseste sa citeasca elementul dimensiune, inseamna ca s-a ajuns la sfarsit de fisier
        // in acest caz se inchide fisierul si se iese din functie
        if (fread(&nNume, sizeof(unsigned short), 1, fis) == 0)
        {
            fclose(fis);
            return;
        }
        char *pNume = (char *)malloc((nNume + 1) * sizeof(char)); // alocare memorie pentru nume si terminator
        if (pNume == NULL)
        {
            printf("memorie insuficienta");
            fclose(fis);
            eliberare();
            exit(EXIT_FAILURE);
        }
        fread(pNume, sizeof(char), nNume, fis); // citire caractere nume
        pNume[nNume] = '\0';                    // deoarece in fisier nu exista terminatorul de sir, acesta se adauga separat
        produse[nProduse].nume = pNume;
        fread(&produse[nProduse].pret, sizeof(float), 1, fis); // citeste pretul produsului
        nProduse++;
    }
}

int main()
{
    int optiune;

    citire(); // citirea bazei de date la inceputul programului
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