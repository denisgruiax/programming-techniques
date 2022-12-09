#include <stdio.h>
#include <string.h>

int f1(int a, int b)
{
    return a + b;
}
int f2(int a, int b)
{
    return a - b;
}
int f3(int a, int b)
{
    return a * b;
}
int f4(int a, int b)
{
    return a / b;
}

int f5(int **(***a)(double))
{
    a[1][2] = f3;
}

int main(int argc, char *argv[])
{
    int(*p[4])(int, int) = {f1, f2, f3, f4};

    printf("add %d\n", p[0](2,2));
    printf("sub %d\n", p[1](2,2));
    printf("mul %d\n", p[2](2,2));
    printf("div %d\n", p[3](2,2));
}