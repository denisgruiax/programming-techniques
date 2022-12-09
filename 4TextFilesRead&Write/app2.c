/*
    Aplicația 4.2: Se citesc m și n de la tastatură, iar apoi o matrice a[m][n].
    Matricea va fi alocată dinamic. Să scrie într-un fișier atât matricea originală cât și transpusa ei,
    separate  printr-o linie goală.
*/

/*
    Pentru unele valori programul returneaza eroarea "segmentation fault"
*/

#include <stdio.h>
#include <stdlib.h>

unsigned lines = 0, columns = 0;
int **matrix, **transpose;

void createMatrix();
void displayMatrix(int **matrix, unsigned lines, unsigned columns);
void freeMatrix(int **matrix, unsigned lines);
void computeTranspose();
void writeToFile();

int main()
{
    createMatrix();
    displayMatrix(matrix, lines, columns);
    computeTranspose();
    displayMatrix(transpose, columns, lines);
    writeToFile();

    freeMatrix(matrix, lines);
    return 0;
}

void createMatrix()
{
    puts("Insert size of lines and columns with one space. (ex -> 3 3)\n");
    scanf("%d %d", &lines, &columns);

    matrix = (int **)calloc(sizeof(int *), lines);
    for (size_t i = 0; i < lines; i++)
        *(matrix + i) = (int *)calloc(sizeof(int), columns);

    if (!matrix)
    {
        freeMatrix(matrix, lines);
        fprintf(stderr, "error on allocating the matrix!");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            *(*(matrix + i) + j) = i * j;
}

void displayMatrix(int **matrix, unsigned lines, unsigned columns)
{
    for (size_t i = 0; i < lines; i++, putchar('\n'))
        for (size_t j = 0; j < columns; j++)
            printf("%d ", *(*(matrix + i) + j));

    putchar('\n');
}

void freeMatrix(int **matrix, unsigned lines)
{
    for (size_t i = 0; i < lines; i++)
        free(*(matrix + i));

    free(matrix);
}

void computeTranspose()
{
    transpose = (int **)calloc(sizeof(int *), columns);
    for (size_t i = 0; i < columns; i++)
        *(transpose + i) = (int *)calloc(sizeof(int), lines);

    if (!transpose)
    {
        freeMatrix(transpose, columns);
        fprintf(stderr, "error on allocating the transpose!");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            *(*(transpose + j) + i) = *(*(matrix + i) + j);
}

void writeToFile()
{
    FILE *file;

    if ((file=fopen("app2.txt", "wt")) == NULL)
    {
        fprintf(stderr, "error on opening the file");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lines; i++, fprintf(file, "\n"))
        for (size_t j = 0; j < columns; j++)
            fprintf(file, " %d ", *(*(matrix + i) + j));

    fprintf(file, "\n");

    for (size_t i = 0; i < columns; i++, fprintf(file, "\n"))
        for (size_t j = 0; j < lines; j++)
            fprintf(file, " %d ", *(*(matrix + i) + j));

    fclose(file);
}