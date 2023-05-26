#include "shell.h"

/**
 * isExitCommand - Check if the command is "exit"
 * @command: Command to check
 * Return: 1 if it is "exit", 0 otherwise
 */
int isExitCommand(char *command)
{
	return (str_compare(command, "exit") == 0);
}

/**
 * EndOfFile - Handle end of file condition
 * @input: Pointer to the input buffer
 * Description: Frees the input buffer and exits the program.
 * If the standard input is a terminal, a newline character is written before exiting.
 * */
void EndOfFile(char *input)
{
	if (input)
	{
		free(input);
		input = NULL;
	}

	if (isatty(STDIN_FILENO))
		_write(STDOUT_FILENO, "\n", 1);
	free(input);
	exit(EXIT_SUCCESS);
}

/**
 * _write - Wrapper function for the write system call
 * @fn: File descriptor
 * @buf: Pointer to the data buffer
 * @byte: Number of bytes to write
 */
void _write(int fn, const void *buf, size_t byte)
{
	write(fn, buf, byte);
}

/**
 * Custom implementation of strcmp function.
 * Compares two strings lexicographically.
 * Returns an integer less than, equal to, or greater than zero
 * if str1 is found to be less than, equal to, or greater than str2, respectively.
 *
 * @param str1 The first string to compare.
 * @param str2 The second string to compare.
 * @return Integer value indicating the comparison result.
 */
int str_compare(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}
	return *(unsigned char *)str1 - *(unsigned char *)str2;
}

/**
 * run - Function to create a child process and execute a command
 * @tokens: Array of command tokens
 * @input: Name of the shell executable
 * @env: Array of environment variables
 * @counts: Number of command cycles
 */
void run(char **tokens, char *input, char **env, int counts)
{
	int pid, stats;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		freexit(tokens);
	}
	else if (pid == 0)
	{
		exec(tokens, input, env, counts);
		freemem(tokens);
	}
	else
	{
		
		if (waitpid(pid, &stats, 0) == -1)
		{
			freexit(tokens);
		}
		freemem(tokens);
	}
}
