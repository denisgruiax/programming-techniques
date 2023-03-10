/*
typedef enum{TMBenzina, TMMotorina, TMElectric}TipMotor;
typedef enum{TVPersoane, TVMarfa, TVSpecial}TipVehicul;

typedef struct{
    TipMotor tm;
    char marca[20];
    TipVehicul tv;
    union{
        struct{
            int nrLocuri;
            int nrAirbaguri;
            }p;
        struct{
            double capacitate;
            char frigorific;		// false (0), true (1)
            }m;
        char special[20];		// "tractor", "balastiera", ...
        }specific;
    } Vehicul;

Aplicația 2.1: Pentru structura Vehicul de mai sus, să se implementeze funcțiile de introducere de la tastatură și de afișare.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    BENZINA,
    MOTORINA,
    ELECTRIC
} TipMotor;

const char str1[][20] = {"benzina", "motorina", "electric"};

typedef enum
{
    PERSOANE,
    MARFA,
    SPECIAL
} TipVehicul;

const char str2[][20] = {"persoane", "marfa", "special"};

typedef struct
{
    TipMotor tipMotor;
    char marca[20];
    TipVehicul tipVehicul;

    union {
        struct
        {
            int nrLocuri;
            int nrAirbaguri;
        } p;
        struct
        {
            double capacitate;
            char frigorific; // false (0), true (1)
        } m;

        char special[20]; // "tractor", "balastiera", ...
    } Specific;

} Vehicul;

void afiseazaDateVehicul(Vehicul *vehicul);
void citesteDateVehicul(Vehicul *vehicul);

int main(int argc, char *argv[])
{
    Vehicul vehicul = {0};
    citesteDateVehicul(&vehicul);
    afiseazaDateVehicul(&vehicul);

    return 0;
}

void afiseazaDateVehicul(Vehicul *vehicul)
{
    printf("\nAfsisare\n\n");

    printf("Tip motor: %s\n", str1[vehicul->tipMotor]);
    printf("Marca: %s\n", vehicul->marca);
    printf("Tip vehicul: %s\n", str2[vehicul->tipVehicul]);

    switch (vehicul->tipVehicul)
    {
    case 0:

        printf("Numar locuri: %i\n", vehicul->Specific.p.nrLocuri);
        printf("Numar airbag-uri: %i\n", vehicul->Specific.p.nrAirbaguri);

        break;

    case 1:
        printf("Capacitate: %0.2f\n", vehicul->Specific.m.capacitate);
        printf("Frigorific: %s\n", (vehicul->Specific.m.frigorific) ? "da" : "nu");
        break;

    case 2:
        printf("Special: %s\n", vehicul->Specific.special);
        break;

    default:
        printf("Optiune gresita\n");
        break;
    }
}

void citesteDateVehicul(Vehicul *vehicul)
{
    char temp, marca[20];
    int temp2;
    double temp3;
    
    printf("Introducere:\n\n");

    printf("tip motor (0 - benzina, 1 - diesel, 2-electric): ");
    scanf("%hhd", &temp);
    vehicul->tipMotor = temp;

    printf("marca (litere): ");
    scanf("%s", &marca);
    strcpy(vehicul->marca, marca);

    printf("Tip vehicul (0-persoane, 1-marfa, 2-special): ");
    scanf("%hhd", &temp);
    vehicul->tipVehicul = temp;

    switch (temp)
    {
    case 0:

        printf("numar locuri (intreg): ");
        scanf("%d", &temp2);
        vehicul->Specific.p.nrLocuri = temp2;

        printf("numar airbag uri (intreg): ");
        scanf("%d", &temp2);
        vehicul->Specific.p.nrAirbaguri = temp2;
        break;

    case 1:

        printf("capacitate (numar in virgula): ");
        scanf("%lf", &temp3);
        vehicul->Specific.m.capacitate = temp3;

        printf("Frogorific ? (0 / 1): ");
        scanf("%hhd", &temp);
        vehicul->Specific.m.frigorific = temp;

        break;

    case 2:

        printf("Rol special ? (litere): ");
        scanf("%s", &marca);
        strcpy(vehicul->Specific.special, marca);

        break;

    default:
        printf("Optiune gresita.\n");
        break;
    }
}