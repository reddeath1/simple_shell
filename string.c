#include "shell.h"

int _strlen(char *s)
{
    if (!s)
        return 0;

    int length = 0;
    while (*s++)
        length++;

    return length;
}

int _strcmp(char *s1, char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 - *s2);
        s1++;
        s2++;
    }

    return (*s1 - *s2);
}

char *starts_with(const char *haystack, const char *needle)
{
    while (*needle)
    {
        if (*needle++ != *haystack++)
            return NULL;
    }

    return (char *)haystack;
}

char *_strcat(char *dest, char *src)
{
    char *ret = dest;

    while (*dest)
        dest++;

    while ((*dest++ = *src++))
        ;

    return ret;
}
