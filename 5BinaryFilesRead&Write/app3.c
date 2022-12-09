/*
    Aplicația 5.3: Se citesc m și n de la tastatură, iar apoi o matrice a[m][n] cu elemente de tip întreg.
    Să se scrie matricea într-un fișier binar, prima oară scriindu-se m și n, iar apoi elementele, așa cum sunt dispuse ele în memorie.
    Să se citească matricea din fișier într-o variabilă b și să se afișeze.
*/

#include <stdio.h>
#include <stdlib.h>

int **initializeMatrix(int **matrix, size_t lines, size_t columns);
void displayMatrix(int **matrix, size_t lines, size_t columns);
int **setMatrix(int **matrix, size_t lines, size_t columns);
void freeMatrix(int **matrix, size_t lines);
void writeInFile(int **matrix, size_t lines, size_t columns);
void readFromFile();

int main()
{
    size_t lines = 3, columns = 3;
    int **matrix = NULL;

    printf("lines: ");
    scanf("%lu", &lines);

    printf("columns: ");
    scanf("%lu", &columns);

    matrix = initializeMatrix(matrix, lines, columns);
    matrix = setMatrix(matrix, lines, columns);

    displayMatrix(matrix, lines, columns);

    writeInFile(matrix, lines, columns);
    readFromFile();

    return 0;
}

int **initializeMatrix(int **matrix, size_t lines, size_t columns)
{
    matrix = (int **)calloc(sizeof(int), lines);

    for (size_t i = 0; i < lines; i++)
    {
        if (!matrix)
        {
            fprintf(stderr, "Error on allocating the matrix. (line: %u)\n", __LINE__);
            exit(EXIT_FAILURE);
        }
        else
        {
            *(matrix + i) = (int *)calloc(sizeof(int), columns);

            if (!*(matrix + i))
            {
                fprintf(stderr, "Error on allocating the matrix[%lu]. (line: %u)\n", i, __LINE__);
                exit(EXIT_FAILURE);
            }
        }
    }

    return matrix;
}

void displayMatrix(int **matrix, size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++, putchar('\n'))
        for (size_t j = 0; j < columns; j++)
            printf("%i ", *(*(matrix + i) + j));
}

int **setMatrix(int **matrix, size_t lines, size_t columns)
{
    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
            printf("matrix[%lu][%lu] = ", i, j), scanf("%i", &matrix[i][j]);

    return matrix;
}

void freeMatrix(int **matrix, size_t lines)
{
    for (size_t i = 0; i < lines; i++)
        free(*(matrix + i));

    free(matrix);
}

void writeInFile(int **matrix, size_t lines, size_t columns)
{
    FILE *output;

    if (!(output = fopen("app3_out.dat", "wb")))
    {
        fprintf(stderr, "Error on opening the file! (line: %u)\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < lines; i++)
        for (size_t j = 0; j < columns; j++)
        {
            fwrite(&i, sizeof(int), 1, output);
            fwrite(&j, sizeof(int), 1, output);
            fwrite(&*(*(matrix + i) + j), sizeof(int), 1, output);
        }

    fclose(output);
}

void readFromFile()
{
    int line = 0, column = 0, value = 0;
    FILE *input = NULL;

    if (!(input = fopen("app3_out.dat", "rb")))
    {
        fprintf(stderr, "Error on opening the file! (line: %u)\n", __LINE__);
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        if (fread(&line, sizeof(int), 1, input) == 0)
        {
            fclose(input);
            return;
        }

        if (fread(&column, sizeof(int), 1, input) == 0)
        {
            fclose(input);
            return;
        }

        if (fread(&value, sizeof(int), 1, input) == 0)
        {
            fclose(input);
            return;
        }

        printf("matrix[%i][%i] = %i\n", line, column, value);
    }

    fclose(input);
}