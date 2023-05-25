#include "shell.h"

char **get_environ(info_t *info)
{
	if (info->environ == NULL || info->env_changed)
	{
		free_string_array(info->environ);
		info->environ = convert_list_to_array(info->env);
		info->env_changed = 0;
	}

	return info->environ;
}

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t index = 0;

	if (node == NULL || var == NULL)
		return 0;

	while (node)
	{
		if (starts_with(node->str, var))
		{
			info->env_changed = delete_node_at_index(&(info->env), index);
			index = 0;
			node = info->env;
			continue;
		}

		node = node->next;
		index++;
	}

	return info->env_changed;
}

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;

	if (var == NULL || value == NULL)
		return 0;

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (buf == NULL)
		return 1;

	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);

	node = info->env;
	while (node)
	{
		if (starts_with(node->str, var))
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return 0;
		}

		node = node->next;
	}

	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return 0;
}
