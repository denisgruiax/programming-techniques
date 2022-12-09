#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *transform(char *string)
{
    *string = toupper(*string);
    while (*string)
    {
        ++string;
        *string = tolower(*string);
    }

    return string;
}

int main(int argc, char *argv[])
{
    char *text = malloc(10);
    strcpy(text, "mARIA");
    transform(text);

    puts(text);

    free(text);
    return 0;
}