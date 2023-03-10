#include <stdio.h>
 
// cantitatea unui produs poate fi data in numar de bucati sau prin greutatea sa, exprimata in kg
union Cantitate{
    int nBucati;
    double kg;
    };
 
struct Produs{
    char um;	// unitate de masura: 'b'-la bucata, 'k'-kilograme
    union Cantitate c;
    };
 
void afisare(struct Produs *p)
{
    switch(p->um){
        case 'b':printf("%d bucati\n",p->c.nBucati);break;
        case 'k':printf("%g kg\n",p->c.kg);break;
        default:printf("unitate de masura invalida\n");
        }
}
 
void introducere(struct Produs *p)
{
    printf("unitate de masura (b sau k): ");
    scanf("%c",&p->um);
    switch(p->um){
        case 'b':
            printf("numar de bucati: ");
            scanf("%d",&p->c.nBucati);
            break;
        case 'k':
            printf("greutate (kg): ");
            scanf("%lg",&p->c.kg);
            break;
        default:printf("unitate de masura invalida\n");
        }
}
 
int main()
{
    struct Produs p;
    introducere(&p);
    afisare(&p);
    return 0;
}
