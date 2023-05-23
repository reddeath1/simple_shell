#include "shell.h"


int _atoi(char *str)
{
        int result = 0;
        int sign = 1;
        int i = 0;

        if (str[0] == '-')
        {
                sign = -1;
                i++;
        }

        while (str[i] != '\0')
        {
                if (str[i] >= '0' && str[i] <= '9')
                {
                        result = result * 10 + (str[i] - '0');
                        i++;
                }
                else
                {
                        break;
                }
        }

        return result * sign;
}

void changeDirectory(char **tokens)
{
        if (tokens[1] == NULL || strcmp(tokens[1], "~") == 0)
        {
                // No argument or ~ provided, change to home directory
                char *homeDir = getenv("HOME");
                if (homeDir == NULL)
                {
                        fprintf(stderr, "Home directory not found\n");
                        return;
                }

                if (chdir(homeDir) != 0)
                {
                        fprintf(stderr, "%s: No such file or directory\n", homeDir);
                }
        }
        else if (strcmp(tokens[1], "-") == 0)
        {
                // "-" provided, change to previous directory
                char *prevDir = getenv("OLDPWD");
                if (prevDir == NULL)
                {
                        fprintf(stderr, "Previous directory not found\n");
                        return;
                }

                if (chdir(prevDir) != 0)
                {
                        fprintf(stderr, "%s: No such file or directory\n", prevDir);
                }
                else
                {
                        printf("%s\n", prevDir);
                }
        }
        else
        {
                // Directory path provided, change to specified directory
                if (chdir(tokens[1]) != 0)
                {
                        fprintf(stderr, "%s: No such file or directory\n", tokens[1]);
                }
        }
}


void tokenizeInput(char *input, char **tokens, int *numTokens)
{
        char *token = strtok(input, " \t\n");
        *numTokens = 0;

        while (token != NULL)
        {
                tokens[*numTokens] = token;
                (*numTokens)++;
                token = strtok(NULL, " \t\n");
        }

        tokens[*numTokens] = NULL;
}
