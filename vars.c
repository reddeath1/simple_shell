#include "shell.h"

/**
 * is_chain -function that checks if current char in buffer is a chain delimeter
 * @d: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(details *d, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		d->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		d->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		d->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @d: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(details *d, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (d->cmd_buf_type == CMD_AND)
	{
		if (d->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (d->cmd_buf_type == CMD_OR)
	{
		if (!d->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @d: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(details *d)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(d->alias, d->argv[0], '=');
		if (!node)
			return (0);
		free(d->argv[0]);
		p = str_locate(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		d->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(details *d)
{
	int i = 0;
	list_t *node;

	for (i = 0; d->argv[i]; i++)
	{
		if (d->argv[i][0] != '$' || !d->argv[i][1])
			continue;

		if (!_strcmp(d->argv[i], "$?"))
		{
			str_replace(&(d->argv[i]),
				_strdup(cn(d->status, 10, 0)));
			continue;
		}
		if (!_strcmp(d->argv[i], "$$"))
		{
			str_replace(&(d->argv[i]),
				_strdup(cn(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(d->env, &d->argv[i][1], '=');
		if (node)
		{
			str_replace(&(d->argv[i]),
				_strdup(str_locate(node->str, '=') + 1));
			continue;
		}
		str_replace(&d->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * str_replace - function to replace string
 * @str: address of old string
 * @str1: new string
 * Return: (Always 1 if replaced, 0 otherwise)
 */
int str_replace(char **str, char *str1)
{
	free(*str);
	*str = str1;
	return (1);
}
