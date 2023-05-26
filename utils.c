#include "shell.h"
/**
 * s_atoi - Convert string to integer
 * @str: String to convert
 * Return: Converted integer value
 */

int s_atoi(char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
		{
			break;
		}
	}

	return (result * sign);
}

/**
 * s_strlen - Calculate the length of a string
 * @str: Input string
 * Return: Length of the string
 */
size_t strlength(const char *str)
{
	const char *s = str;

	while (*s)
		++s;
	return (s - str);
}

/**
 * _getline - Read a line of input from stdin
 * @lineptr: Pointer to store the allocated line
 * @n: Pointer to store the allocated size
 * Return: Number of bytes read or -1 on failure
 */
ssize_t sgetline(char **lineptr, size_t *n)
{
	ssize_t read_bytes = 0;
	size_t buffer_size = 0;
	char *buffer = NULL, *new_buffer = NULL;
	int c;
	char *line = NULL;
	ssize_t i = 0;
	size_t new_size = 0;

	if (lineptr == NULL || n == NULL)
	{
		return (-1);
	}

	while ((c = getchar()) != '\n' && c != EOF)
	{
		if (read_bytes >= (ssize_t)buffer_size)
		{
			new_size = buffer_size + 1;
			new_buffer = realloc(buffer, new_size);

			if (new_buffer == NULL)
			{
				free(buffer);
				return (-1);
			}
			buffer = new_buffer;
			buffer_size = new_size;
		}

		buffer[read_bytes++] = c;
	}

	if (read_bytes > 0)
	{
		line = malloc(read_bytes + 1);
		if (line == NULL)
		{
			free(buffer);
			return (-1);
		}

		for (; i < read_bytes; i++)
		{
			line[i] = buffer[i];
		}

		line[read_bytes] = '\0';
		*lineptr = line;
	}
	else
	{
		*lineptr = NULL;
	}

	*n = buffer_size;

	free(buffer);

	if (c == EOF)
	{
		return (-1);
	}

	return (read_bytes);
}

/**
 * s_chdir - Change directory
 * @tokens: Array of tokens
 * Return: Always 1 or 0
 */
int s_chdir(char **tokens)
{
	char *buf = NULL;
	size_t size = 1024;

	if (tokens == NULL)
		tokens[1] = getcwd(buf, size);

	if (chdir(tokens[1]) == -1)
	{
		perror(tokens[1]);
		return (98);
	}
	return (1);
}

char *strcopy(char *dest, char *src)
{
	char *aux = dest;

	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (aux);
}
