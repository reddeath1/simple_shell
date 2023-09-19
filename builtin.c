#include "shell.h"

/**
 * myexit - function that exits the shell
 * @d: Structure containing arguments.
 *  Return: )exits with a given exit status)
 */
int myexit(details *d)
{
	int exitcheck;

	if (d->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = err_atoi(d->argv[1]);
		if (exitcheck == -1)
		{
			d->status = 2;
			perrors(d, "Illegal number: ");
			error_put(d->argv[1]);
			error_putchar('\n');
			return (1);
		}
		d->err_num = err_atoi(d->argv[1]);
		return (-2);
	}
	d->err_num = -1;
	return (-2);
}

/**
 * mycd - changes the current directory of the process
 * @d: Structure containing  arguments.
 *  Return: Always 0
 */
int mycd(details *d)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!d->argv[1])
	{
		dir = _getenv(d, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(d, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(d->argv[1], "-") == 0)
	{
		if (!_getenv(d, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(d, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(d, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(d->argv[1]);
	if (chdir_ret == -1)
	{
		perrors(d, "can't cd to ");
		error_put(d->argv[1]), error_putchar('\n');
	}
	else
	{
		_setenv(d, "OLDPWD", _getenv(d, "PWD="));
		_setenv(d, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myhelp - changes the current directory of a process
 * @d: Structure containing potential arguments.
 *  Return: (Always 0)
 */
int myhelp(details *d)
{
	char **arg_array;

	arg_array = d->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
