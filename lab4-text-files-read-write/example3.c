#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **linii; // vector de linii: char *linii[]
int nLinii;
FILE *fin;  // fisierul de intrare
FILE *fout; // fisierul de iesire

void eliberare()
{
    int i;
    for (i = 0; i < nLinii; i++)
        free(linii[i]);
    free(linii);
    fclose(fin);
    fclose(fout);
}

void adauga(const char *linie) // adauga o linie in linii
{
    // duplica linia
    char *linieNoua = (char *)malloc((strlen(linie) + 1) * sizeof(char));

    if (!linieNoua)
    {
        printf("memorie insuficienta");
        eliberare();
        exit(EXIT_FAILURE);
    }
    strcpy(linieNoua, linie);
    // face loc in linii pentru linia noua
    
    char **p = (char **)realloc(linii, (nLinii + 1) * sizeof(char *));

    if (!p)
    {
        printf("memorie insuficienta");
        free(linieNoua);
        eliberare();
        exit(EXIT_FAILURE);
    }
    linii = p;
    linii[nLinii] = linieNoua;
    nLinii++;
}

// functia de comparare pentru qsort
// deoarece qsort transmite elementele vectorului prin adresele lor
// si fiecare element din linii este un sir de caractere (char*)
// inseamna ca de fapt se va transmite char** (adresa unui sir de caractere)
int cmp(const void *p1, const void *p2)
{
    // se transmit lui strcmp valorile pointate de sirurile de caractere transmise prin adresa
    // strcmp are aceeasi conventie pentru valorile returnate ca si qsort
    // deci valoarea returnata de strcmp se poate returna direct lui qsort
    return strcmp(*(char **)p1, *(char **)p2);
}

int main(void)
{
    char linie[1000];
    int i;
    // citeste liniile din fisierul de intrare
    if ((fin = fopen("example3_linii.txt", "r")) == NULL)
    {
        printf("eroare deschidere fisier de intrare\n");
        exit(EXIT_FAILURE);
    }
    while (fgets(linie, 1000, fin) != NULL)
    { // atata timp cat se citeste o linie de intrare
        // daca linia este vida, nu o adauga in vectorul de linii
        // linia e vida daca s-a ajuns la sfarsit de fisier sau daca este doar un \n
        if (strlen(linie) <= 1)
            continue;
        adauga(linie);
    }
    // nu mai este nevoie de fisierul de intrare, deci se putea inchide aici. va fi inchis la sfarsit, de eliberare()

    qsort(linii, nLinii, sizeof(char *), cmp);

    // scrie liniile sortate in fisierul de iesire
    if ((fout = fopen("example3_sortate.txt", "w")) == NULL)
    {
        printf("eroare deschidere fisier de iesire\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < nLinii; i++)
        fputs(linii[i], fout);
    fclose(fout);
    //eliberare(); -> at this line the program has an error -> "free(): double free detected in tcache 2, Aborted"
    return 0;
}
