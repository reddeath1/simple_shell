#include "shell.h"

/**
 * clearinfo - initializes info_t struct
 * @d: struct address
 */
void clearinfo(details *d)
{
	d->arg = NULL;
	d->argv = NULL;
	d->path = NULL;
	d->argc = 0;
}

/**
 * setinfo - function to initializes struct details 
 * @d: struct address
 * @av: argument vector
 */
void setinfo(details *d, char **av)
{
	int i = 0;

	d->fname = av[0];
	if (d->arg)
	{
		d->argv = strtow(d->arg, " \t");
		if (!d->argv)
		{

			d->argv = malloc(sizeof(char *) * 2);
			if (d->argv)
			{
				d->argv[0] = _strdup(d->arg);
				d->argv[1] = NULL;
			}
		}
		for (i = 0; d->argv && d->argv[i]; i++)
			;
		d->argc = i;

		replace_alias(d);
		replace_vars(d);
	}
}

/**
 * freeinfo - function to free details struct fields
 * @info: struct address
 * @a: freeing all fields
 */
void freeinfo(details *d, int a)
{
	sfree(d->argv);
	d->argv = NULL;
	d->path = NULL;
	if (a)
	{
		if (!d->cmd_buf)
			free(d->arg);
		if (d->env)
			free_list(&(d->env));
		if (d->history)
			free_list(&(d->history));
		if (d->alias)
			free_list(&(d->alias));
		sfree(d->envi);
			d->env = NULL;
		pointer_free((void **)d->cmd_buf);
		if (d->rfd > 2)
			close(d->rfd);
		_putchar(BUF_FLUSH);
	}
}
