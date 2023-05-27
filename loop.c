#include "shell.h"

/**
 * hsh_loop - main function shell loop
 * @d: the parameter & return info struct
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh_loop(details *d, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clearinfo(d);
		if (interact(d))
			_puts("$ ");
		error_putchar(BUF_FLUSH);
		r = _input(d);
		if (r != -1)
		{
			setinfo(d, av);
			builtin_ret = is_builtin(d);
			if (builtin_ret == -1)
				find_cmd(d);
		}
		else if (interact(d))
			_putchar('\n');
		freeinfo(d, 0);
	}
	write_history(d);
	freeinfo(d, 1);
	if (!interact(d) && d->status)
		exit(d->status);
	if (builtin_ret == -2)
	{
		if (d->err_num == -1)
			exit(d->status);
		exit(d->err_num);
	}
	return (builtin_ret);
}

/**
 * is_builtin - function that finds a builtin command
 * @d: the parameter & return info struct
 * Return: Always 0 or 1
 */
int is_builtin(details *d)
{
	int i, built_in_ret = -1;
	builtins builtin[] = {
		{"exit", myexit},
		{"env", myenv},
		{"help", myhelp},
		{"history", myhistory},
		{"setenv", mysetenv},
		{"unsetenv", myunsetenv},
		{"cd", mycd},
		{"alias", myalias},
		{NULL, NULL}
	};

	for (i = 0; builtin[i].type; i++)
		if (_strcmp(d->argv[0], builtin[i].type) == 0)
		{
			d->line_c++;
			built_in_ret = builtin[i].func(d);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - functions that finds a command in PATH
 * @d: the parameter & return info struct
 * Return: void
 */
void find_cmd(details *d)
{
	char *path = NULL;
	int i, k;

	d->path = d->argv[0];
	if (d->linecount_flag == 1)
	{
		d->line_c++;
		d->linecount_flag = 0;
	}
	for (i = 0, k = 0; d->arg[i]; i++)
		if (!_delim(d->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = is_path(d, _getenv(d, "PATH="), d->argv[0]);
	if (path)
	{
		d->path = path;
		fork_cmd(d);
	}
	else
	{
		if ((interact(d) || _getenv(d, "PATH=")
			|| d->argv[0][0] == '/') && is_command(d, d->argv[0]))
			fork_cmd(d);
		else if (*(d->arg) != '\n')
		{
			d->status = 127;
			perrors(d, "not found\n");
		}
	}
}

/**
 * fork_cmd - function that forks a an exec thread to run cmd
 * @d: the parameter & return info struct
 * Return: void
 */
void fork_cmd(details *d)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perrors(d,"Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(d->path, d->argv, get_environ(d)) == -1)
		{
			freeinfo(d, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(d->status));
		if (WIFEXITED(d->status))
		{
			d->status = WEXITSTATUS(d->status);
			if (d->status == 126)
				perrors(d, "Permission denied\n");
		}
	}
}
