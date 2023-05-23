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

		return result * sign;
}

/**
 * s_strlen - Calculate the length of a string
 * @str: Input string
 * Return: Length of the string
 */
size_t s_strlen(const char *str)
{
		const char *s = str;
		while (*s)
				++s;
		return s - str;
}

/**
 * _getline - Read a line of input from stdin
 * @lineptr: Pointer to store the allocated line
 * @n: Pointer to store the allocated size
 * Return: Number of bytes read or -1 on failure
 */
ssize_t _getline(char **lineptr, size_t *n)
{

	// Initialize variables
	ssize_t read_bytes = 0;
	size_t buffer_size = 0;
	char *buffer = NULL, *new_buffer = NULL;
	int c;
	char *line = NULL;
	ssize_t i = 0;
	size_t new_size = 0;

	if (lineptr == NULL || n == NULL)
	{
		return -1;
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
				return -1;
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
			return -1;
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
		return -1;
	}

	return read_bytes;
}

/**
 * s_chdir - Change directory
 * @tokens: Array of tokens
 */
void s_chdir(char **tokens)
{
	if (tokens[1] == NULL || strcmp(tokens[1], "~") == 0)
	{
		char *homeDir = getenv("HOME");
		if (homeDir == NULL)
		{
			fprintf(stderr, "Home directory not found\n");
			return;
		}

		if (chdir(homeDir) != 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", homeDir);
		}
	}
	else if (strcmp(tokens[1], "-") == 0)
	{
		char *prevDir = getenv("OLDPWD");
		if (prevDir == NULL)
		{
			fprintf(stderr, "Previous directory not found\n");
			return;
		}

		if (chdir(prevDir) != 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", prevDir);
		}
		else
		{
			printf("%s\n", prevDir);
		}
	}
	else
	{
		if (chdir(tokens[1]) != 0)
		{
			fprintf(stderr, "%s: No such file or directory\n", tokens[1]);
		}
	}
}
