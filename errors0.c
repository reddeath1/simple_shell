#include "shell.h"

/**
 * err_atoi - convert a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int err_atoi(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * perrors - function that print an error message
 * @p: a parameter & return info struct
 * @er: a string containing specified error type
 * Return: (0 if no numbers in string, converted number -1 on error)
 */
void perrors(details *p, char *er)
{
	error_put(p->fname);
	error_put(": ");
	display_decimal(p->line_c, STDERR_FILENO);
	error_put(": ");
	error_put(p->argv[0]);
	error_put(": ");
	error_put(er);
}

/**
 * display_decimal - function prints a decimal integer number of base 10
 * @input:  input
 * @fd:  filedescriptor to write to
 * Return: (number of characters printed)
 */
int display_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cn - A converter function
 * @nu: number
 * @_base: base
 * @flags: argument flags
 * Return:( string)
 */
char *cn(long int nu, int _base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = nu;

	if (!(flags & TO_UNSIGNED) && nu < 0)
	{
		n = -nu;
		sign = '-';

	}
	array = flags & TO_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % _base];
		n /= _base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rm_comments - function that replaces first instance of '#' with '\0'
 * @input: address of the string to modify
 * Return: Always 0;
 */
void rm_comments(char *input)
{
	int i;

	for (i = 0; input[i] != '\0'; i++)
		if (input[i] == '#' && (!i || input[i - 1] == ' '))
		{
			input[i] = '\0';
			break;
		}
}
