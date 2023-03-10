#include <stdio.h>

int positive(int element);
int even(int element);
int testing(int *v, int n, int (*cond)(int));

int main(int argc, char *argv[])
{
    int v[] = {4, 8, 1, 2, 0};

    printf("All the elements are positive: %d\n", testing(v, 5, positive));
    printf("All the elements are even: %d\n", testing(v, 5, even));

    return 0;
}

int positive(int element)
{
    return (element >= 0);
}

int even(int element)
{
    return (element % 2 == 0);
}

int testing(int *v, int n, int (*cond)(int))
{
    for (unsigned i = 0; i < n; i++)
        if (!cond(v[i]))
            return 0;

    return 1;
}