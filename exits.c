#include "shell.h"

char *_strncpy(char *dest, char *src, int n)
{
	char *s = dest;

	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dest++ = '\0';
		n--;
	}

	return s;
}

char *_strncat(char *dest, char *src, int n)
{
	char *s = dest;

	while (*dest)
		dest++;
	while (*src && n > 0)
	{
		*dest++ = *src++;
		n--;
	}
	*dest = '\0';

	return s;
}

char *_strchr(char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return s;
		s++;
	}

	return NULL;
}
