#include "shell.h"

/**
 * is_command - function that determines
 * if file is an executable command or not
 * @d: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_command(details *d, char *path)
{
	struct stat st;

	(void)d;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_duplicates - function returns duplicates characters
 * @path: PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *char_duplicates(char *path, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path[i] != ':')
			buf[k++] = path[i];
	buf[k] = 0;
	return (buf);
}

/**
 * is_path - function that finds command in the PATH string
 * @d: the info struct
 * @paths:PATH string
 * @cmdn:commandd to find
 * Return: (full path or NULL)
 */
char *is_path(details *d, char *paths, char *cmdn)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!paths)
		return (NULL);
	if ((_strlen(cmdn) > 2) && starts_with(cmdn, "./"))
	{
		if (is_command(d, cmdn))
			return (cmdn);
	}
	while (1)
	{
		if (!paths[i] || paths[i] == ':')
		{
			path = char_duplicates(paths, curr_pos, i);
			if (!*path)
				_strcat(path, cmdn);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmdn);
			}
			if (is_command(d, path))
				return (path);
			if (!paths[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
