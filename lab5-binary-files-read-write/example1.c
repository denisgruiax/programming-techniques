#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    FILE *fis;
    int n[] = {0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD, 0x1177AAEE, 0xAABBCCDD};
    
    if((fis=fopen("example1.dat","wb"))==NULL){
        printf("nu se poate deschide fisierul\n");
        exit(EXIT_FAILURE);
        }
 
    fwrite(&n,sizeof(int),20,fis);
 
    fclose(fis);
    return 0;
}
