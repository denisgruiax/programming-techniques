/*
    Aplicația 2.5: Se consideră că o măsurătoare are asociată unitatea de măsură (gram, metru, litru) și multiplicatorul acesteia (pico, nano, mili, centi, deci, deca, hecto, kilo, mega, giga).
    Să se codifice o măsurătoare astfel încât să conțină o valoare întreagă pozitivă care să acopere un interval cât mai mare de valori, unitatea de măsură și multiplicatorul acesteia. O măsurătoare va ocupa exact 2 octeți.
    Să se citească o valoare unsigned și o unitate de măsură. La citire nu există multiplicator. Să se determine multiplicatorul astfel încât valoarea stocată să fie cât mai mică, fără a se pierde precizie, iar apoi să se stocheze într-o măsurătoare. Dacă valoarea nu încape, se va afișa o eroare. Să se afișeze toate câmpurile măsurătorii.
    Exemplu: valoare=147000, unitate:gram     =>     147 kilogram
*/
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    pico,
    nano,
    mili,
    centi,
    deci,
    base,
    deca,
    hecto,
    kilo,
    mega,
    giga
} Multiply;

char *multiplyNames[15] = {"pico", "nano", "mili", "centi", "deci", "base",
                           "deca", "hecto", "kilo", "mega", "giga"};

typedef enum
{
    gram,
    meter,
    liter
} Group;

char *groupNames[15] = {"gram", "meter", "liter"};

typedef struct
{
    unsigned number : 16;
} Store;

void readVars(unsigned *number, Multiply *mul, Group *group);
void writeStructure(Store *store, unsigned number, Multiply *mul, Group group);
void readStructure(Store *store, Multiply mul, Group group);

int main(int argc, char *argv[])
{
    Store store;
    unsigned number;
    Multiply mul;
    Group group;

    readVars(&number, &mul, &group);
    writeStructure(&store, number, &mul, group);

    printf("\n%lu\n", sizeof(store));
    readStructure(&store, mul, group);
    
    return 0;
}

void readVars(unsigned *number, Multiply *mul, Group *group)
{
    unsigned temp;

    puts("Group");
    scanf("%u", &temp);
    *group = temp;

    puts("Number:");
    scanf("%u", number);

    puts("Multiply:");
    scanf("%u", &temp);
    *mul = temp;
}

void writeStructure(Store *store, unsigned number, Multiply *mul, Group group)
{
    while ((number % 10) == 0)
    {
        if (*mul == giga)
            break;

        number /= 10;
        (*mul)++;
    }

    store->number = number;
}
void readStructure(Store *store, Multiply mul, Group group)
{
    printf("%u ", store->number);

    if ((mul) == 5)
        printf("%s\n", groupNames[group]);
    else
        printf("%s%s\n", multiplyNames[mul], groupNames[group]);
}
