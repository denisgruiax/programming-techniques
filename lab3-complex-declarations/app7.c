/*
    Aplicația 3.8: Folosind funcții polimorfice, să se implementeze o colecție eterogenă de produse. 
    Vor fi 2 tipuri de produse: calculatoare, definite prin {nume CPU, capacitate memorie în GB} și monitoare, 
    definite prin {diagonală în inch, rezoluție orizontală, rezoluție verticală}. Singura funcție polimorfică va fi afisare, 
    care afișează tipul și toate proprietățile unui produs pe o linie. De exemplu, dacă avem un calculator și un monitor, 
    afișarea va fi de forma:
    calculator: cpu:Ryzen, memorie:8GB
    monitor: diagonala:24, rezolutie:1920x1080
*/

/*NOT SOLVED, BELOW IS SOMETHING ELSE*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14159

void *allocateMemory(unsigned nBytes)
{
    void *tempPointer = malloc(nBytes);

    if (!tempPointer)
    {
        puts("No enough memory..");
        exit(EXIT_FAILURE);
    }

    return tempPointer;
}

struct _Form;
typedef struct _Form Form;

typedef struct
{
    double (*area)(Form *f);
    double (*perimeter)(Form *f);
    char *(*name)(Form *f);

} VTable;

struct _Form
{
    VTable *vTable;
};

//Circle begin

typedef struct
{
    Form form;
    double r;
    char *name;
} Circle;

double Circle_area(Form *form)
{
    Circle *circle = (Circle *)form;
    return PI * pow((circle->r), 2);
}

double Circle_perimeter(Form *form)
{
    Circle *circle = (Circle *)form;
    return (2 * PI * (circle->r));
}

char *Circle_name(Form *form)
{
    Circle *circle = (Circle *)form;
    return circle->name;
}

VTable vTable_circle = {Circle_area, Circle_perimeter, Circle_name};

Circle *Circle_new(double r, char *name)
{
    Circle *circle = (Circle *)allocateMemory(sizeof(Circle));

    circle->form.vTable = &vTable_circle;
    circle->r = r;

    circle->name = allocateMemory(strlen(name));
    strcpy(circle->name, name);

    return circle;
}

//Circle end

//Traingle begin

typedef struct
{
    Form form;
    double s1, s2, s3; //sides of triangle
    char *name;
} Triangle;

double Triangle_area(Form *form)
{
    Triangle *tri = (Triangle *)form;
    double sP = (tri->s1 + tri->s2 + tri->s3); //semi perimeter

    return (sqrt(sP * (sP - tri->s1) * (sP - tri->s2) * (sP - tri->s3))); //area
}

double Triangle_perimeter(Form *form)
{
    Triangle *tri = (Triangle *)form;

    return (tri->s1 + tri->s2 + tri->s3);
}

char *Triangle_name(Form *form)
{
    Triangle *tri = (Triangle *)form;
    return (tri->name);
}

VTable vTable_triangle = {Triangle_area, Triangle_perimeter, Triangle_name};

Triangle *Triangle_new(double s1, double s2, double s3, char *name)
{
    Triangle *tri = (Triangle *)allocateMemory(sizeof(Triangle));

    tri->form.vTable = &vTable_triangle;
    tri->s1 = s1;
    tri->s2 = s2;
    tri->s3 = s3;

    tri->name = allocateMemory(strlen(name));
    strcpy(tri->name, name);

    return tri;
}
//Triangle end

int main(int argc, char *argv[])
{
    Form *forms[100];
    int i = 0, nForms = 0;

    forms[nForms++] = (Form *)Circle_new(1, "asdads1");
    forms[nForms++] = (Form *)Triangle_new(6, 8, 10, "tadse34");

    for (i = 0; i < nForms; i++)
    {
        printf("%g\n", forms[i]->vTable->perimeter(forms[i]));
    }

    putchar('\n');

    for (i = 0; i < nForms; i++)
    {
        printf("%g\n", forms[i]->vTable->area(forms[i]));
    }
    
    putchar('\n');

    for (i = 0; i < nForms; i++)
    {
        printf("%s\n", forms[i]->vTable->name(forms[i]));
    }

    for (i = 0; i < nForms; i++)
    {
        free(forms[i]);
    }
    
}
