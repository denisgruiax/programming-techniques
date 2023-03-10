#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159

void *alocare(size_t nOcteti)
{
    void *p = malloc(nOcteti);

    if (!p)
    {
        printf("memorie insuficienta\n");
        exit(EXIT_FAILURE);
    }

    return p;
}

// predeclararea structurii Figura, deoarece ea este folosita in VTable inainte de a fi definita
struct _Figura;
typedef struct _Figura Figura;

typedef struct
{
    double (*arie)(Figura *f);      // pointer la functia care va calcula aria elementului f
    double (*perimetru)(Figura *f); // pointer la functia care va calcula perimetrul elementului f
} VTable;

struct _Figura
{                   // structura initiala din care vor fi derivate toate tipurile de elemente
    VTable *vTable; // pointer la vTable-urile specifice fiecarui tip de figura
};

typedef struct
{
    Figura figura; // figura trebuie sa fie pe prima pozitie in tipurile derivate din Figura, pentru a se putea folosi campul vTable indiferent de tipul elementului (in orice tip, vTable va fi la offsetul 0 fata de inceputul structurii)
    double r;      // elemente specifice unui cerc
} Cerc;

// functiile care implementeaza functiile polimorfice pentru tipul Cerc
double Cerc_arie(Figura *f)
{
    Cerc *c = (Cerc *)f;
    return PI * c->r * c->r;
}

double Cerc_perimetru(Figura *f)
{
    Cerc *c = (Cerc *)f;
    return 2 * PI * c->r;
}

// variabila care contine pointeri la implementarile functiilor polimorfice pentru Cerc
VTable vTable_cerc = {Cerc_arie, Cerc_perimetru};

Cerc *Cerc_new(double r)
{
    Cerc *c = (Cerc *)alocare(sizeof(Cerc));
    c->figura.vTable = &vTable_cerc; // seteaza pointerul vTable la structura cu functiile specifice pentru Cerc
    c->r = r;
    return c;
}

// implementariile mele
typedef struct
{
    Figura figura;
    double latura;
    double lungime;
} Dreptunghi;

double Dreptunghi_arie(Figura *figura)
{
    Dreptunghi *dreptunghi = (Dreptunghi *)figura;
    return dreptunghi->latura * dreptunghi->lungime;
}

double Dreptunghi_perimetru(Figura *figura)
{
    Dreptunghi *dreptunghi = (Dreptunghi *)figura;
    return 2 * (dreptunghi->latura + dreptunghi->lungime);
}

VTable vTable_dreptunghi = {Dreptunghi_arie, Dreptunghi_perimetru};

Dreptunghi *Dreptunghi_new(double latura, double lungime)
{
    Dreptunghi *dreptunghi = (Dreptunghi *)alocare(sizeof(Dreptunghi));
    
    dreptunghi->figura.vTable = &vTable_dreptunghi;
    dreptunghi->latura = latura;
    dreptunghi->lungime = lungime;

    return dreptunghi;
}

typedef struct
{
    Figura figura;
    double latura, latura2, latura3;
} Triunghi;

double Triunghi_arie(Figura *figura)
{
    Triunghi *triunghi = (Triunghi *)figura;

    double semiPerimetru = (triunghi->latura + triunghi->latura2 + triunghi->latura3) / 2;

    return sqrt(semiPerimetru * (semiPerimetru - triunghi->latura) * (semiPerimetru - triunghi->latura2) * (semiPerimetru - triunghi->latura3));
}

double Triunghi_perimetru(Figura *figura)
{
    Triunghi *triunghi = (Triunghi *)figura;
    return triunghi->latura + triunghi->latura2 + triunghi->latura3;
}

VTable vTable_triunghi = {Triunghi_arie, Triunghi_perimetru};

Triunghi *Triunghi_new(double latura, double latura2, double latura3)
{
    Triunghi *triunghi = (Triunghi *)alocare(sizeof(Triunghi));
    
    triunghi->figura.vTable = &vTable_triunghi;
    triunghi->latura = latura;
    triunghi->latura2 = latura2;
    triunghi->latura3 = latura3;

    return triunghi;
}

// analogic se implementeaza triunghiul si dreptunghiul

int main(void)
{
    Figura *figuri[100]; // vector de pointeri la figuri alocate dinamic
    int i, nFiguri = 0;
    // introducere figuri
    figuri[nFiguri++] = (Figura *)Cerc_new(1);
    figuri[nFiguri++] = (Figura *)Dreptunghi_new(2, 4);
    figuri[nFiguri++] = (Figura *)Triunghi_new(3, 4, 5);
    //  afisare perimetre
    for (i = 0; i < nFiguri; i++)
    {
        printf("%g\n", figuri[i]->vTable->perimetru(figuri[i]));
        printf("%g\n\n", figuri[i]->vTable->arie(figuri[i]));   
    }
    return 0;
}