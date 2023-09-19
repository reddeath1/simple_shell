#include "shell.h"

/**
 * get_history_file - function that gets the history file
 * @d: parameter struct
 * Return: (allocated string containg history file)
 */

char *get_history_file(details *d)
{
	char *buf, *dir;

	dir = _getenv(d, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HISTORY_FILE);
	return (buf);
}

/**
 * write_history - function that creates a file, or appends to an existing file
 * @d: the parameter struct
 * Return:( 1 on success, else -1)
 */
int write_history(details *d)
{
	ssize_t fd;
	char *filename = get_history_file(d);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = d->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(FLUSH_BUFFER, fd);
	close(fd);
	return (1);
}

/**
 * read_history - function that reads history from file
 * @d: parameter struct
 * Return: (count on success, 0 otherwise)
 */
int read_history(details *d)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(d);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(d, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(d, buf + last, linecount++);
	free(buf);
	d->histcount = linecount;
	while (d->histcount-- >= HISTORY_MAX)
		delete_node_at_index(&(d->history), 0);
	renumber_history(d);
	return (d->histcount);
}

/**
 * build_history_list -function that
 * adds entry to history linked
 * list
 * @d: structure containing arguments.
 * @buf: buffer
 * @count: history line count, hist count
 * Return: (Always 0)
 */
int build_history_list(details *d, char *buf, int count)
{
	list_t *node = NULL;

	if (d->history)
		node = d->history;
	add_node_end(&node, buf, count);

	if (!d->history)
		d->history = node;
	return (0);
}

/**
 * renumber_history - function that renumbers
 * the history linked list after the changes
 * @d: structure containing arguments.
 * Return: (histcount)
 */
int renumber_history(details *d)
{
	list_t *node = d->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (d->histcount = i);
}
