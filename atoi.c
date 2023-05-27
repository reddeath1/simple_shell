#include "shell.h"

/**
 * interact- check if shell is interactive mode
 * @d: struct address
 * Return: allows 1 or 0
 */
int interact(details *d)
{
	return (isatty(STDIN_FILENO) && d->rfd <= 2);
}

/**
 * _delim - check if character is a delimeter
 * @c: char to check
 * @delimiter: delimeter string
 * Return: 1 if true, 0 if false
 */
int _delim(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 *_alpha - alphabetic character checker
 *@input:  input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _alpha(int input)
{
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - a function that converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int i, si = 1, flag = 0, output;
	unsigned int results = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			si *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			results *= 10;
			results += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (si == -1)
		output = -results;
	else
		output = results;

	return (output);
}
