/*
Aplicația 2.3: Se citește de la tastatură o linie de text care conține o atribuire a unei variabile cu o valoare. 
Linia are forma ”nume_variabila=valoare”. Numele variabilei poate conține doar litere sau cifre, cu restricția ca primul caracter să fie literă. 
Valoarea poate fi număr (începe cu o cifră și poate avea zecimale), 
caracter (începe cu apostrof) sau șir de caractere (începe cu ghilimele). Câteva exemple de astfel de atribuiri:
    raza=10.12
    B22 = 'c'
    adresa="Bd. Vasile Parvan nr. 2"
Folosind struct și union definiți o structură de date pentru a păstra în mod eficient informația din linia citită de la tastatură. 
Transferați informația din linia citită într-o variabilă de tipul structurii de date definite. 
Afișați informația păstrată în variabilă, folosind formatul original (nume_variabila=valoare). 
Tratați posibile erori ce pot să apară în linia citită (nume incorect de variabilă, lipsește semnul egal, 
valoarea atribuită este invalidă).
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum
{
    CHAR,
    INT,
    DOUBLE,
    STRING,
    BAD,
    OK
} Type;

char *typesName[20] = {"character", "integer", "double", "string", "bad", "ok"};
typedef struct
{
    Type type;
    char name[20];
    union
    {
        char character;
        int integer;
        double floating;
        char str[20];
    } U;

} Variable;

char *getString();
void disassembly(char *p, char *name, char *value);
char analyzeName(char *name);
char analyzeValue(char *name);
void writeStructure(Variable *var, char *name, char *value);
void readStructure(Variable *var);

int main(int argc, char *argv[])
{
    char *str = getString(), name[20], value[20];
    Variable var;
    disassembly(str, name, value);

    if (analyzeName(name) == OK)
    {
        writeStructure(&var, name, value);
        readStructure(&var);
    }
    else
        printf("Bad name.\n");

    return 0;
}

char *getString()
{
    unsigned size = 0;
    char *store, character;

    for (;;)
    {
        size++;
        character = getchar();
        store = (char *)realloc(store, size);
        if (character != '\n')
            store[size - 1] = character;
        else
        {
            store[size - 1] = '\0';
            break;
        }
    }

    return store;
}

void disassembly(char *str, char *name, char *value)
{
    for (;;)
    {
        if (*str == '=')
        {
            str++, *name = '\0';
            break;
        }

        *name = *str;
        str++, name++;
    }

    while (*str != '\0')
    {
        *value = *str;
        str++;
        value++;
    }
}

char analyzeName(char *name)
{
    if (!isalpha(name[0]))
        return BAD;

    for (unsigned i = 1; i < strlen(name); i++)
    {
        if (!(isalpha(name[0]) || !(isdigit((name[0])))))
            return BAD;
    }

    return OK;
}
char analyzeValue(char *value)
{
    unsigned size = strlen(value);

    if (value[0] == '"' && (value[size - 1] == '"'))
        return STRING;
    else if (((value[0] == '\'') && (value[size - 1] == '\'')) && strlen(value) < 4)
        return CHAR;
    else
    {
        char flag = 0;

        for (unsigned i = 0; i < size; i++)
        {
            if (!isdigit(value[i]) && value[i] != '.')
                return BAD;

            if (value[i] == '.' && flag == 1)
            {
                return BAD;
            }

            if (value[i] == '.')
                flag = 1;
        }

        if (flag)
            return DOUBLE;
        else
            return INT;
    }

    return BAD;
}

void writeStructure(Variable *var, char *name, char *value)
{
    var->type = (Type)analyzeValue(value);
    strcpy(var->name, name);

    switch (var->type)
    {
    case CHAR:
        var->U.character = value[1];
        break;

    case INT:
        var->U.integer = atoi(value);
        break;

    case DOUBLE:
        var->U.floating = atof(value);
        break;

    case STRING:
        strcpy(var->U.str, value);
        break;
    default:
        printf("Bad option");
        break;
    }
}
void readStructure(Variable *var)
{
    printf("\nName: %s\n", var->name);
    printf("Type: %s\n", typesName[var->type]);
    switch (var->type)
    {
    case CHAR:
        printf("value = %c\n", var->U.character);
        break;

    case INT:
        printf("value = %i\n", var->U.integer);
        break;

    case DOUBLE:
        printf("value = %0.5f\n", var->U.floating);
        break;

    case STRING:
        printf("value = %s\n", var->U.str);
        break;

    default:
        printf("Bad option.\n");
        break;
    }
}
