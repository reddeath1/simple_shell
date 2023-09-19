#include "shell.h"

/**
 * main - Main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	details inf[] = { INFO };
	int d = 2;

	if (argc > 1)
	{
		d = open(argv[1], O_RDONLY);
		if (d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_put(argv[0]);
				error_put(": 0: Can not open ");
				error_put(argv[1]);
				error_putchar('\n');
				error_putchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->rfd = d;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh_loop(inf, argv);
	return (EXIT_SUCCESS);
}
