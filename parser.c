#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
    struct stat st;

    if (!path || stat(path, &st) != 0)
        return 0;

    return S_ISREG(st.st_mode);
}

/**
 * find_path - finds the given command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the command to find
 *
 * Return: full path of cmd if found, or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
    if (!pathstr || !cmd)
        return NULL;

    if (strncmp(cmd, "./", 2) == 0 && is_cmd(info, cmd))
        return cmd;

    char *path = strtok(pathstr, ":");
    while (path)
    {
        size_t path_len = strlen(path);
        size_t cmd_len = strlen(cmd);

        char *full_path = malloc((path_len + cmd_len + 2) * sizeof(char));
        if (!full_path)
            return NULL;

        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (is_cmd(info, full_path))
            return full_path;

        free(full_path);
        path = strtok(NULL, ":");
    }

    return NULL;
}
