/*
    Aplicația 1.9: Un program primește în linia de comandă o expresie formată din numere reale 
    și operatorii {add-adunare, sub-scădere, mul-înmulțire, div-împărțire}. 
    Programul va calcula valoarea expresiei și va afișa rezultatul. 
    Expresia se calculează de la stânga la dreapta, fără a ține cont de precedența matematică a operatorilor.
    Exemplu: ./calcul 10.5 add 1.5 div 3           va afișa: 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double calculate(int counter, char *arguments[]);

int main(int counter, char *arguments[])
{
    double sum = calculate(counter, arguments);
    printf("%0.0f\n", sum);
}

double calculate(int counter, char *arguments[])
{
    double sum = atof(arguments[1]);    

    for (unsigned i = 2; i < counter; i += 2)
    {
        if (!strcmp(arguments[i], "add"))
        {
            sum += atof(arguments[i + 1]);
        }
        if (!strcmp(arguments[i], "sub"))
        {
            sum -= atof(arguments[i + 1]);
        }
        if (!strcmp(arguments[i], "mul"))
        {
            sum *= atof(arguments[i + 1]);
        }
        if (!strcmp(arguments[i], "div"))
        {
            sum /= atof(arguments[i + 1]);
        }
    }

    return sum;
}