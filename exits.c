#include "shell.h"

/**
 *_strncpy - function that copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: (concatenated string)
 */
char *_strncpy(char *dest, char *src, int n)
{
	int x, v;
	char *str = dest;

	x = 0;
	while (src[x] != '\0' && x < n - 1)
	{
		dest[x] = src[x];
		x++;
	}
	if (x < n)
	{
		v = x;
		while (v < n)
		{
			dest[v] = '\0';
			v++;
		}
	}
	return (str);
}

/**
 *_strncat - function that concatenates two strings
 *@dest: arg
 *@src: arg
 *@n: amount of bytes to be used
 *Return: (concatenated string)
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, v;
	char *str = dest;

	i = 0;
	v = 0;
	while (dest[i] != '\0')
		i++;
	while (src[v] != '\0' && v < n)
	{
		dest[i] = src[v];
		i++;
		v++;
	}
	if (v < n)
		dest[i] = '\0';
	return (str);
}

/**
 *str_locate - function that locates a character in a string
 *@str: string to be parsed
 *@cha:  character to look for
 *Return: ((s) pointer to the memory area s)
 */
char *str_locate(char *str, char cha)
{
	do {
		if (*str == cha)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
