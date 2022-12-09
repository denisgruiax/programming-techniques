#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Pt;

FILE *fis;  // declarat global pentru a putea fi inchis din adauga() in caz de eroare
Pt *puncte; // initializat implicit cu NULL
int nPuncte;

void adauga(double x, double y) // adauga un punct in puncte
{
    Pt *p = (Pt *)realloc(puncte, (nPuncte + 1) * sizeof(Pt));
    if (!p)
    {
        printf("memorie insuficienta");
        free(puncte);
        fclose(fis);
        exit(EXIT_FAILURE);
    }
    puncte = p;
    puncte[nPuncte].x = x;
    puncte[nPuncte].y = y;
    nPuncte++;
}

// transmitere de structuri prin valoare
double dist(Pt p1, Pt p2)
{
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

int main(void)
{
    int i, j;
    double x, y;
    if ((fis = fopen("example2_puncte.txt", "r")) == NULL)
    {
        printf("eroare deschidere fisier\n");
        exit(EXIT_FAILURE);
    }
    while (fscanf(fis, "%lg%lg", &x, &y) == 2)
    {                 // atata timp cat se citesc puncte
        adauga(x, y); // adauga punctul citit in vector
    }
    fclose(fis); // nu mai este nevoie de fisier
    if (!nPuncte)
    {
        printf("fisier vid\n");
        exit(EXIT_FAILURE);
    }
    double dMax = 0;        // presupunem distanta maxima ca fiind 0
    int iMax = 0, jMax = 0; // indecsii punctelor celor mai departate intre ele
    for (i = 0; i < nPuncte; i++)
    {
        for (j = i + 1; j < nPuncte; j++)
        {
            double d = dist(puncte[i], puncte[j]);
            if (d > dMax)
            { // daca s-a gasit o pereche de puncte mai distantate, actualizeaza rezultatul
                iMax = i;
                jMax = j;
                dMax = d;
            }
        }
    }
    printf("punctele cele mai departate: (%g,%g) - (%g,%g)\n",
           puncte[iMax].x, puncte[iMax].y, puncte[jMax].x, puncte[jMax].y);
    free(puncte);
    return 0;
}
