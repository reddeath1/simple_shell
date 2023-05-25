#include "shell.h"

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return NULL;

	int dir_len = _strlen(dir);
	int hist_file_len = _strlen(HIST_FILE);
	int buf_size = dir_len + hist_file_len + 2;

	buf = malloc(sizeof(char) * buf_size);
	if (!buf)
		return NULL;

	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);

	return buf;
}

int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	if (!filename)
		return -1;

	ssize_t fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return -1;

	list_t *node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}

	_putfd(BUF_FLUSH, fd);
	close(fd);

	return 1;
}

int read_history(info_t *info)
{
	char *filename = get_history_file(info);
	if (!filename)
		return 0;

	int fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return 0;

	struct stat st;
	if (fstat(fd, &st) != 0)
	{
		close(fd);
		return 0;
	}

	off_t fsize = st.st_size;
	if (fsize < 2)
	{
		close(fd);
		return 0;
	}

	char *buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
	{
		close(fd);
		return 0;
	}

	ssize_t rdlen = read(fd, buf, fsize);
	close(fd);

	if (rdlen <= 0)
	{
		free(buf);
		return 0;
	}

	buf[fsize] = '\0';
	int linecount = 0;
	char *line = buf;

	while (*line != '\0')
	{
		char *newline = strchr(line, '\n');
		if (newline)
			*newline = '\0';

		build_history_list(info, line, linecount++);
		line = newline + 1;
	}

	free(buf);
	info->histcount = linecount;

	while (info->histcount >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);

	renumber_history(info);

	return info->histcount;
}

int build_history_list(info_t *info, char *buf, int linecount)
{
	add_node_end(&(info->history), buf, linecount);
	return 0;
}

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}

	return (info->histcount = i);
}
