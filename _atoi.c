#include "shell.h"
#include <unistd.h>

int interactive(info_t *info)
{
    return isatty(STDIN_FILENO) && info->readfd <= 2;
}

int is_delim(char c, char *delim)
{
    while (*delim != '\0')
    {
        if (*delim == c)
            return 1;
        delim++;
    }
    return 0;
}

int _isalpha(int c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int _atoi(char *s)
{
    int sign = 1;
    unsigned int result = 0;
    int flag = 0;
    int i = 0;

    while (s[i] != '\0' && flag != 2)
    {
        if (s[i] == '-')
            sign *= -1;

        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result = result * 10 + (s[i] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }

        i++;
    }

    if (sign == -1)
        return -result;
    else
        return result;
}

