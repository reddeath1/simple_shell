#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @dest: the destination
 * @src: the source
 * Return: (pointer to a destination)
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - function to duplicates a string
 * @s: string to duplicate
 * Return: (pointer to the duplicated string)
 */
char *_strdup(const char *s)
{
	int length = 0;
	char *r;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;
	r = malloc(sizeof(char) * (length + 1));
	if (!r)
		return (NULL);
	for (length++; length--;)
		r[length] = *--s;
	return (r);
}

/**
 *_puts - function that prints an input string
 *@s: the string to be printed
 * Return: (Nothing)
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}

/**
 * _putchar - function to write the character c to stdout
 * @cha: The character to print
 * Return: (On success 1, On error, -1 is returned).
 */
int _putchar(char cha)
{
	static int i;
	static char buf[INPUT_WRITE_BUF_SIZE];

	if (cha == FLUSH_BUFFER || i >= INPUT_WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (cha != FLUSH_BUFFER)
		buf[i++] = cha;
	return (1);
}
