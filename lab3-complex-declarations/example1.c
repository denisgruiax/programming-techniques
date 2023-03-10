#include <stdio.h>

int f1(int a, int b);
int f2(int a, int b);

int main(int argc, char *argv[])
{
    int a = 7, b = 5;
    int (*p)(int, int);

    p = f1;
    printf("op1 (%d, %d) = %d\n", a, b, (*p)(a, b));
    p = f2;
    printf("op2 (%d, %d) = %d\n", a, b, (*p)(a, b));

    return 0;
}

int f1(int a, int b)
{
    return a + b;
}

int f2(int a, int b)
{
    return a - b;
}
