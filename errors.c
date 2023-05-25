#include "shell.h"

void _eputs(char *str)
{
	if (str == NULL)
		return;

	while (*str != '\0')
	{
		_eputchar(*str);
		str++;
	}
}

int _eputchar(char c)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i] = c;
		i++;
	}

	return 1;
}

int _putfd(char c, int fd)
{
	static int i = 0;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i] = c;
		i++;
	}

	return 1;
}

int _putsfd(char *str, int fd)
{
	if (str == NULL)
		return 0;

	int count = 0;

	while (*str != '\0')
	{
		count += _putfd(*str, fd);
		str++;
	}

	return count;
}
