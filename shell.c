#include "shell.h"
/**
 * main - Main function
 * @argc: Number of arguments
 * @a: pointer to array arguments
 * @evn: Pointer to enviroment variable arrays
 * Return: (Always 0)
 */

int main()
{
        char *input;
        char *tokens[MAX_TOKENS];
        int numTokens;

        while (1)
        {
                prompter();

                input = _getline();

                tokenizeInput(input, tokens, &numTokens);

                if (fgets(input, sizeof(input), stdin) == NULL)
                {
                        // End of file (Ctrl+D) is encountered
                        printf("\n");
                        break;
                }

                // Tokenize input
                tokenizeInput(input, tokens, &numTokens);

                if (numTokens > 0)
                {
                        if (strcmp(tokens[0], "alias") == 0)
                        {
                                executeAliasCommand(tokens);
                        }
                        else if (strcmp(tokens[0], "cd") == 0)
                        {
                                changeDirectory(tokens);
                        }
                        else if (isExitCommand(tokens[0]))
                        {
                                // Check for additional argument
                                if (numTokens > 1)
                                {
                                        // Convert status argument to integer
                                        int status = _atoi(tokens[1]);

                                        // Exit the shell with status
                                        exit(status);
                                }
                                else
                                {
                                        // Exit the shell without status
                                        break;
                                }
                        }
                        else
                        {
                                executeCommand(tokens);
                        }
                }
        }

        return 0;
}

/**
 * prompter - funtion to display prompts
 * Return: always null
 */
void prompter()
{
        printf("Shell> ");
        fflush(stdout);
}

char *_getline()
{
    static char buffer[MAX_INPUT_SIZE];
    static int bufferIndex = 0;
    static int bytesRead = 0;

    char *line = &buffer[bufferIndex];
    int lineLength = strcspn(line, "\n");
    bufferIndex += lineLength + 1;

    if (line[lineLength] == '\n')
    {
        // Remove the newline character
        line[lineLength] = '\0';
    }

    return line;
}

int isExitCommand(char *command)
{
        return strcmp(command, "exit") == 0;
}

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

void displayAliases()
{
        for (int i = 0; i < numAliases; i++)
        {
                printf("%s='%s'\n", aliases[i].name, aliases[i].value);
        }
}

void displayAlias(const char *name)
{
        for (int i = 0; i < numAliases; i++)
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
        for (int i = 0; i < numAliases; i++)
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

void executeAliasCommand(char **tokens)
{
        if (tokens[1] == NULL)
        {
                // No arguments provided, display all aliases
                displayAliases();
                return;
        }

        int tokenIndex = 1;
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

void executeCommand(char **tokens)
{
        pid_t pid = fork();

        if (pid < 0)
        {
                fprintf(stderr, "Fork failed\n");
                exit(1);
        }
        else if (pid == 0)
        {
                // Child process
                if (execvp(tokens[0], tokens) == -1)
                {
                        fprintf(stderr, "%s: Command not found\n", tokens[0]);
                        exit(1);
                }
        }
        else
        {
                // Parent process
                wait(NULL);
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