/*
    Aplicația 3.6: Să se completeze exemplul de implementare a colecțiilor eterogene folosind pointeri la 
    funcții cu tipul de elemente Triunghi. Un triunghi este definit prin lungimile laturilor sale
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

VTable vTable_circle = {Circle_area, Circle_perimeter};

Circle *Circle_new(double r)
{
    Circle *circle = (Circle *)allocateMemory(sizeof(Circle));

    circle->form.vTable = &vTable_circle;
    circle->r = r;

    return circle;
}

//Circle end

//Traingle begin

typedef struct
{
    Form form;
    double s1, s2, s3; //sides of triangle
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

VTable vTable_triangle = {Triangle_area, Triangle_perimeter};

Triangle *Triangle_new(double s1, double s2, double s3)
{
    Triangle *tri = (Triangle *)allocateMemory(sizeof(Triangle));
    
    tri->form.vTable = &vTable_triangle;
    tri->s1 = s1;
    tri->s2 = s2;
    tri->s3 = s3;

    return tri;
}
//Triangle end

int main(int argc, char *argv[])
{
    Form *forms[100];
    int i = 0, nForms = 0;

    forms[nForms++] = (Form *)Circle_new(1);
    forms[nForms++] = (Form *)Triangle_new(6, 8, 10);

    for (i = 0; i < nForms; i++)
    {
        printf("%g\n", forms[i]->vTable->perimeter(forms[i]));
    }
    
    putchar('\n');
    
    for (i = 0; i < nForms; i++)
    {
        printf("%g\n", forms[i]->vTable->area(forms[i]));
    }
}
