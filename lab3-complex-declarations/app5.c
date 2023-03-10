/*
    Aplicația 3.5: Să se implementeze o funcție care tabelează o funcție matematică de un parametru, primită ca argument. 
    Funcția tabelată primește un parametru de tip double și returnează o valoare tot de tip double. 
    Funcția de tabelare va primi ca parametri: a și b - capetele de tip double ale intervalului închis de tabelat, 
    n - un număr întreg care arată în câte segmente egale se împarte intervalul [a,b], incluzând capetele acestuia 
    și f - funcția de tabelat. Să se testeze funcția de tabelare cu valori a,b și n citite de la tastatură, 
    tabelând funcțiile cos, sqrt și fabs din math.h
    Exemplu: tabelare(-10,10,20,fabs) va afișa pe câte o linie valori de forma f(-10)=10  f(-9)=9   … f(10)=10
*/

#include <stdio.h>
#include <math.h>

void func(double first, double last, double divider, double (*v)(double));

int main(int argc, char *argv[])
{
    func(0, 90, 90, sin);
    func(0, 90, 180, cos);
    func(-10, 10, 20, fabs);
}

void func(double first, double last, double divider, double (*v)(double))
{
    double inc = (last - first) / divider;
    unsigned position = 0;

    for (double count = first; count <= last; count += inc, position++)
    {
        if (inc <= 0)
            break;

        printf("f(%u) = %0.1f\n", position, v(count));
    }

    putchar('\n');
}