/*
    Aplicația 3.1: Se cere un număr n și apoi un vector de n rezultate ale studenților la un examen. 
    Fiecare rezultat este definit prin (nume,nota). Se cere să se sorteze folosind qsort vectorul în ordinea notelor, 
    notele cele mai mari fiind primele. Dacă două note sunt identice, rezultatele respective se vor sorta în ordinea 
    alfabetică a numelor.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char student[20];
    double grade;
} Students;

int compare2(const void *elem1, const void *elem2);

int main(int argc, char *argv[])
{
    Students students[8] = {
        {"denis", 7.75},
        {"alex", 9.98},
        {"ionut", 8.90},
        {"andrei", 10},
        {"denisa", 7.75},
        {"andrei", 7.12},
        {"ionut", 10},
        {"maria", 8.99}
    };

    qsort(students, 8, sizeof(Students), compare2);

    for (unsigned i = 0; i < 8; i++)
        printf("%s %f\n", (students + i)->student, (students + i)->grade);

    return 0;
}

int compare2(const void *elem1, const void *elem2)
{
    const Students *student1 = (const Students *)elem1;
    const Students *student2 = (const Students *)elem2;

    if ((student1->grade) < (student2->grade))
        return 1;
    if ((student1->grade) > (student2->grade))
        return -1;

    if (strcmp(student1->student, student2->student) == -1)
        return 1;
    else
        return -1;
}