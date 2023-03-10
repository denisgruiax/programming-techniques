#include <stdio.h>
#include <string.h>

int main()
{
    FILE *file1, *file2, *file3;
    char *forFile1 = "Denis are mere.",
         *forFile2 = "Deniss arre as asd mere pre.",
         *forFile3 = "Dines yrx merf.";

    file1 = fopen("file1.dat", "wb");
    file2 = fopen("file2.dat", "wb");
    file3 = fopen("file3.dat", "wb");

    fwrite(forFile1, sizeof(char), strlen(forFile1), file1);
    fwrite(forFile2, sizeof(char), strlen(forFile2), file2);
    fwrite(forFile3, sizeof(char), strlen(forFile3), file3);

    fclose(file1);
    fclose(file2);
    fclose(file3);
}