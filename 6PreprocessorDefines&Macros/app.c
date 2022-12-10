#include <stdio.h>

#define M1(a, b) a * b + 1        // nicio paranteza
#define M2(a, b) (a) * (b) + 1   // paranteze doar in jurul argumentelor
#define M3(a, b) (a * b + 1)     // paranteze doar in jurul macroului
#define M4(a, b) ((a) * (b) + 1) // paranteze in jurul argumentelor si a macroului

int main()
{
    printf("%d\n", -M1(2 + 3, 4 + 5));
    printf("%d\n", -M2(2 + 3, 4 + 5));
    printf("%d\n", -M3(2 + 3, 4 + 5));
    printf("%d\n", -M4(2 + 3, 4 + 5));
    return 0;
}
