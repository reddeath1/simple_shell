#include "shell.h"
#include <stdio.h>

int _myenv(info_t *info)
{
    list_t *node = info->env;

    while (node != NULL)
    {
        printf("%s\n", node->str);
        node = node->next;
    }

    return 0;
}

char *_getenv(info_t *info, const char *name)
{
    list_t *node = info->env;

    while (node != NULL)
    {
        if (strncmp(node->str, name, strlen(name)) == 0)
            return node->str;

        node = node->next;
    }

    return NULL;
}

int _mysetenv(info_t *info)
{
    if (info->argc != 3)
    {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    if (setenv(info->argv[1], info->argv[2], 1) == 0)
        return 0;

    return 1;
}

int _myunsetenv(info_t *info)
{
    int i;

    if (info->argc < 2)
    {
        printf("Too few arguments.\n");
        return 1;
    }

    for (i = 1; i < info->argc; i++)
        unsetenv(info->argv[i]);

    return 0;
}

int populate_env_list(info_t *info)
{
    extern char **environ;
    char **envp = environ;
    list_t *node = NULL;

    while (*envp != NULL)
    {
        add_node_end(&node, *envp, 0);
        envp++;
    }

    info->env = node;

    return 0;
}
