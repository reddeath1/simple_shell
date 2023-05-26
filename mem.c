#include "shell.h"

void freemem(char **tokens)
{
	size_t x = 0;

	if (tokens == NULL)
		return;

	while (tokens[x])
	{
		free(tokens[x]);
		x++;
	}

	if (tokens[x] == NULL)
		free(tokens[x]);
	free(tokens);
}

void freexit(char **tokens)
{
	size_t i = 0;

	if (tokens == NULL)
		return;

	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}

	if (tokens[i] == NULL)
		free(tokens[i]);
	free(tokens);
	exit(EXIT_FAILURE);
}
