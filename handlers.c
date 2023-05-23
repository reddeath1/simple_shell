#include "shell.h"

int isExitCommand(char *command)
{
    return strcmp(command, "exit") == 0;
}

void displayAliases(void)
{
    int i = 0;

    for (; i < numAliases; i++)
    {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void displayAlias(const char *name)
{
    int i = 0;

    for (; i < numAliases; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
}

void setAlias(const char *name, const char *value)
{
    int i = 0;

    for (; i < numAliases; i++)
    {
        if (strcmp(aliases[i].name, name) == 0)
        {
            strncpy(aliases[i].value, value, sizeof(aliases[i].value) - 1);
            return;
        }
    }

    if (numAliases < MAX_ALIAS_SIZE)
    {
        strncpy(aliases[numAliases].name, name, sizeof(aliases[numAliases].name) - 1);
        strncpy(aliases[numAliases].value, value, sizeof(aliases[numAliases].value) - 1);
        numAliases++;
    }
}

void executeAliasCommand(char **tokens)
{
    int tokenIndex = 1;

    if (tokens[1] == NULL)
    {
        // No arguments provided, display all aliases
        displayAliases();
        return;
    }

    while (tokens[tokenIndex] != NULL)
    {
        if (strchr(tokens[tokenIndex], '=') != NULL)
        {
            // Define or update an alias
            char *name = strtok(tokens[tokenIndex], "=");
            char *value = strtok(NULL, "=");
            if (name != NULL && value != NULL)
            {
                setAlias(name, value);
            }
            else
            {
                fprintf(stderr, "%s: Invalid alias format\n", tokens[tokenIndex]);
            }
        }
        else
        {
            // Display an alias
            displayAlias(tokens[tokenIndex]);
        }

        tokenIndex++;
    }
}

ssize_t _getline(char **lineptr, size_t *n) {
    static char buffer[MAX_INPUT_SIZE];
    static size_t buffer_index = 0;
    static ssize_t bytes_read = 0;
    size_t line_index = 0;
    char current_char;

    if (bytes_read <= 0) {
        bytes_read = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
        buffer_index = 0;
    }

    if (bytes_read <= 0) {
        // End of file or error encountered
        return -1;
    }

    while (buffer_index < (size_t) bytes_read) {
        if (line_index >= *n - 1) {
            // Resize lineptr if needed
            size_t new_size = *n * 2;
            char *new_lineptr = realloc(*lineptr, new_size);
            if (!new_lineptr) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            *lineptr = new_lineptr;
            *n = new_size;
        }

        current_char = buffer[buffer_index++];
        if (current_char == '\n') {
            (*lineptr)[line_index] = '\0';
            return line_index;
        }

        (*lineptr)[line_index++] = current_char;
    }

    bytes_read = 0; // Mark buffer as empty
    return line_index;
}
