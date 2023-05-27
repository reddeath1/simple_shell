#include "shell.h"

/**
 * get_environ - function that returns the string array copy of our environ
 * @d: Structure containing arguments.
 * Return: Always 0
 */
char **get_environ(details *d)
{
	if (!d->envi || d->env_changed)
	{
		d->envi = list_to_strings(d->env);
		d->env_changed = 0;
	}

	return (d->envi);
}

/**
 * _unsetenv - function that removes an environment variable
 * @d: Structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(details *d, char *var)
{
	list_t *node = d->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			d->env_changed = delete_node_at_index(&(d->env), i);
			i = 0;
			node = d->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (d->env_changed);
}

/**
 * _setenv - function that Initialize a new environment variable,
 *             or modify an existing one
 * @d: Structure containing potential arguments.
 * @str: string env var property
 * @value: string env var value
 *  Return: Always 0
 */
int _setenv(details *d, char *str, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!str || !value)
		return (0);

	buf = malloc(_strlen(str) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, str);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = d->env;
	while (node)
	{
		p = starts_with(node->str, str);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			d->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(d->env), buf, 0);
	free(buf);
	d->env_changed = 1;
	return (0);
}
