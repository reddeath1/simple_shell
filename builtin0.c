#include "shell.h"

/**
 * myhistory - funtion displays the history list
 * @d: Structure containing  arguments.
 *  Return: Always 0
 */
int myhistory(details *d)
{
	print_list(d->history);
	return (0);
}

/**
 * unset_alias - function that sets alias to string
 * @d: parameter struct
 * @str: string alias
 * Return: (Always 0 on success, 1 on error)
 */
int unset_alias(details *d, char *str)
{
	char *p, c;
	int ret;

	p = str_locate(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(d->alias),
		get_node_index(d->alias, node_starts_with(d->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - function that sets alias to string
 * @d: parameter struct
 * @str: string alias
 * Return: (Always 0 on success, 1 on error)
 */
int set_alias(details *d, char *str)
{
	char *p;

	p = str_locate(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(d, str));

	unset_alias(d, str);
	return (add_node_end(&(d->alias), str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_locate(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myalias - function that mimics the alias builtin (man alias)
 * @info: Structure containing arguments.
 *  Return: Always 0
 */
int myalias(details *d)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (d->argc == 1)
	{
		node = d->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; d->argv[i]; i++)
	{
		p = str_locate(d->argv[i], '=');
		if (p)
			set_alias(d, d->argv[i]);
		else
			print_alias(node_starts_with(d->alias, d->argv[i], '='));
	}

	return (0);
}
