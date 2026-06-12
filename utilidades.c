#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* UtilidadesStringTrim(char* str)
{
    char* fin;

    while (isspace(*str))
    {
        str++;
    }

    if (*str == '\0')
    {
        return str;
    }        

    fin = str + strlen(str) - 1;

    while (fin > str && isspace(*fin))
    {
        fin--;
    }

    *(fin + 1) = '\0';

    return str;
}