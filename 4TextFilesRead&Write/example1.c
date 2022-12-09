#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fis;
    int i, n;

    printf("n=");
    scanf("%d", &n);
    
    if ((fis = fopen("example1.txt", "w")) == NULL)
    { // deschidere fisier pentru scriere (w - write)
        printf("eroare deschidere fisier\n");
        exit(EXIT_FAILURE);
    }
    
    for (i = 0; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            fprintf(fis, "%d este par\n", i); // fprintf(fis,...) - file printf
        }
        else
        {
            fprintf(fis, "%d este impar\n", i);
        }
    }
    
    fclose(fis); // închidere fisier
    return 0;
}
