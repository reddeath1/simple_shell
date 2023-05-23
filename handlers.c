#include "shell.h"

int isExitCommand(char *command)
{
    return strcmp(command, "exit") == 0;
}

void displayAliases(void)
{
    int i = 0;
    int numAliases = 0;

    for (; i < numAliases; i++)
    {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void displayAlias(const char *name)
{
    int i = 0;
    int numAliases = 0;

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
    int numAliases = 0;

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

