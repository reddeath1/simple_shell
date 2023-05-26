#include "shell.h"
/**
 * exec - Executes shell commands.
 * @tokens: Array of command tokens.
 * @input: Name of the input.
 * @env: Array of environment variables.
 * @counts: Number of command execution cycles.
 */
void exec(char **tokens, char *input, char **env, int counts)
{
	char **paths = NULL, *path = NULL;
	struct stat stc;
	unsigned int i = 0;

	if (stat(tokens[0], &stc) == 0)
	{
		if (execve(tokens[0], &input, env) == -1)
		{
			perror(input);
			freexit(tokens);
		}
	}
	else
	{
		paths = get_PATH(env);
		while (paths[i] && stat((path = str_concat(paths[i++], tokens[0])), &stc) == -1)
			;
		if (paths[i])
			if (execve(path, tokens, env) == -1)
			{
				perror(input);
				freemem(paths);
				freexit(tokens);
			}
		print_error(input, counts, tokens);
		freemem(paths);
	}
}

/**
 * str_concat - Custom implementation of strcat function.
 * Concatenates the source string to the end of the destination string.
 *
 * @destination: Pointer to the destination string.
 * @source: Pointer to the source string.
 *
 * Return: Pointer to the modified destination string.
 */
char *str_concat(char *destination, const char *source)
{
	char *ptr = destination;

	while (*ptr)
	{
		ptr++;
	}

	while (*source)
	{
		*ptr++ = *source++;
	}

	*ptr = '\0';

	return destination;
}

/**
 * print_error - Prints an error message indicating the command was not found.
 * @name: The name of the shell.
 * @counts: The number of command execution cycles.
 * @tokens: The command that was not found.
 */
void print_error(char *name, int counts, char **tokens)
{
	char c = counts + '0';

	_write(STDOUT_FILENO, name, strlength(name)), _write(STDOUT_FILENO, ": ", 2);
	_write(STDOUT_FILENO, &c, 1), _write(STDOUT_FILENO, ": ", 2);
	_write(STDOUT_FILENO, tokens[0], strlength(tokens[0]));
	_write(STDOUT_FILENO, ": not found\n", 12);
}

/**
 * display_env - Dsiplays the environment variables.
 * @env: Array of environment variables.
 */
void display_env(char **env)
{
	size_t va_arg = 0, length = 0;

	while (env[va_arg] != NULL)
	{
		length = strlength(env[va_arg]);
		_write(STDOUT_FILENO, env[va_arg], length);
		_write(STDOUT_FILENO, "\n", 1);
		va_arg++;
	}
}

/**
 * get_PATH - Get the value of the PATH environment variable
 * @env: Array of environment variables
 * Return: Array of directories in the PATH or NULL if not found
 */
char **get_PATH(char **env)
{
	char *value = NULL;
	char **paths = NULL;
	unsigned int i = 0;

	value = strtok(env[i], "=");
	while (env[i] != NULL)
	{
		if (str_compare(value, "PATH") == 0)
		{
			value = strtok(NULL, "\n");
			paths = tokenizeInput(value, ":");
			return paths;
		}
		i++;
		value = strtok(env[i], "=");
	}
	return NULL;
}
