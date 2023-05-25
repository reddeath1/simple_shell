#include "shell.h"

char **split_string(char *str, char *delim)
{
    if (str == NULL || str[0] == '\0')
        return NULL;

    int num_words = 0;
    char **result = NULL;
    char *token;

    if (!delim)
        delim = " ";

    token = strtok(str, delim);
    while (token != NULL) {
        result = realloc(result, (num_words + 1) * sizeof(char *));
        if (!result) {
            free_split_string(result, num_words);
            return NULL;
        }
        result[num_words] = strdup(token);
        num_words++;
        token = strtok(NULL, delim);
    }

    result = realloc(result, (num_words + 1) * sizeof(char *));
    if (!result) {
        free_split_string(result, num_words);
        return NULL;
    }
    result[num_words] = NULL;
    return result;
}

char **split_string2(char *str, char delim)
{
    if (str == NULL || str[0] == '\0')
        return NULL;

    int num_words = 0;
    char **result = NULL;
    char *token;

    token = strtok(str, &delim);
    while (token != NULL) {
        result = realloc(result, (num_words + 1) * sizeof(char *));
        if (!result) {
            free_split_string(result, num_words);
            return NULL;
        }
        result[num_words] = strdup(token);
        num_words++;
        token = strtok(NULL, &delim);
    }

    result = realloc(result, (num_words + 1) * sizeof(char *));
    if (!result) {
        free_split_string(result, num_words);
        return NULL;
    }
    result[num_words] = NULL;
    return result;
}

void free_split_string(char **str_arr, int num_words)
{
    if (str_arr == NULL)
        return;

    for (int i = 0; i < num_words; i++)
        free(str_arr[i]);

    free(str_arr);
}
