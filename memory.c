#include "shell.h"

/**
 * pointer_free - function to frees a pointer and NULL the address
 * @addr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int pointer_free(void **addr)
{
	if (addr && *addr)
	{
		free(*addr);
		*addr = NULL;
		return (1);
	}
	return (0);
}
