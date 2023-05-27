#include "shell.h"

/**
 *error_put - function to print an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void error_put(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		error_putchar(str[i]);
		i++;
	}
}

/**
 * error_putchar - function that writes the character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_putchar(char c)
{
	static int i;
	static char buf[INPUT_WRITE_BUF_SIZE];

	if (c == FLUSH_BUFFER || i >= INPUT_WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[INPUT_WRITE_BUF_SIZE];

	if (c == FLUSH_BUFFER || i >= INPUT_WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfd - function that prints an input string
 * @str:string to be printed
 * @fd:filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
