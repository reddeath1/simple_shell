#include "shell.h"

/**
 * myenv - function that prints the current environment
 * @d: Structure containing  arguments.
 * Return: Always 0
 */
int myenv(details *d)
{
	display_list_string(d->env);
	return (0);
}

/**
 * _getenv - function that gets the value of an environ variable
 * @d: Structure containing arguments
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(details *d, const char *name)
{
	list_t *node = d->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenv - function that initialize a new environment variable,
 *             or modify an existing,
 * @d: Structure containing  arguments
 *  Return: Always 0
 */
int mysetenv(details *d)
{
	if (d->argc != 3)
	{
		error_put("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(d, d->argv[1], d->argv[2]))
		return (0);
	return (1);
}

/**
 * myunsetenv - function that Remove an environment variable
 * @d: Structure containing  argumentsconstant function prototype.
 *  Return: Always 0
 */
int myunsetenv(details *d)
{
	int i;

	if (d->argc == 1)
	{
		error_put("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= d->argc; i++)
		_unsetenv(d, d->argv[i]);

	return (0);
}

/**
 * populate_env_list - function that populates env linked list
 * @d: Structure containing  arguments
 * Return: Always 0
 */
int populate_env_list(details *d)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	d->env = node;
	return (0);
}
