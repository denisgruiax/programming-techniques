/*
    Aplicația 4.1: Se citesc de la tastatură maxim 100 numere reale, până la întâlnirea numărului 0. 
    Să se sorteze aceste numere și să se scrie într-un fișier, toate numerele fiind pe o singură linie, 
    separate prin | (bară verticală).
*/

#include <stdio.h>
#include <stdlib.h>

void sortVector(float *vector, unsigned count);
void writeFile(FILE *file, float *vector, unsigned count);

int main(void)
{
    float *vector, number;
    unsigned count = 1;
    FILE *file;

    if (!(file = fopen("app1_result.txt", "w")))
    {
        puts("eroare\n");
        exit(EXIT_FAILURE);
    }

    vector = (float *)malloc(count * sizeof(float));

    if (!vector)
    {
        puts("eroare");
        exit(EXIT_FAILURE);
    }

    puts("Insert numbers");
    scanf("%f", &number);

    vector[count - 1] = number;

    for (;;)
    {
        scanf("%f", &number);

        if (!number)
            break;

        count++;
        
        vector = (float *)realloc(vector, count * sizeof(float));
        if (!vector)
        {
            puts("eroare");
            exit(EXIT_FAILURE);
        }

        vector[count - 1] = number;
    }

    sortVector(vector, count);
    writeFile(file, vector, count);
    
    free(vector);
    fclose(file);

    return 0;
}

void sortVector(float *vector, unsigned count)
{
    float temp;

    for (unsigned i = 0; i < count; i++)
        for (unsigned j = i; j < (count-1); j++)
        {
            if (vector[j] > vector[j + 1])
            {
                temp = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = temp;
            }
        }
}

void writeFile(FILE *file, float *vector, unsigned count)
{
    for (unsigned i = 0; i < count; i++)
    {
        fprintf(file, "%f |", vector[i]);
    }
}