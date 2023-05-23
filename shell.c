#include "shell.h"
/**
 * main - Main function
 * Return: (Always 0)
 */
int main(int argc, char* argv[], char **env)
{
    char *input = NULL;
    char *tokens[MAX_TOKENS];
    int numTokens;
    size_t input_size = 0;
    ssize_t read_bytes;
    char* executable = NULL;

    if (argc > 0) {
        executable = argv[0];
    }

    while (1)
    {
        prompter();

        read_bytes = _getline(&input, &input_size);

        if (read_bytes == -1)
        {
            // End of file (Ctrl+D) is encountered or error occurred
            break;
        }

        // Remove newline character from the input
        input[strcspn(input, "\n")] = '\0';

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
                s_chdir(tokens);
            }
            else if (isExitCommand(tokens[0]))
            {
                // Check for additional argument
                if (numTokens > 1)
                {
                    // Convert status argument to integer
                    int status = s_atoi(tokens[1]);

                    // Exit the shell with status
                    exit(status);
                }
                else
                {
                    free(input);
                    exit(EXIT_SUCCESS);
                }
            }
            else
            {
                executeCommand(tokens,executable);
            }
        }
        free(input);
        input = NULL;
        input_size = 0;
    }

    // Free allocated memory for input
    free(input);

    return 0;
}

/**
 * prompter - funtion to display prompts
 * Return: always null
 */
void prompter(void)
{
    printf("Shell> ");
    fflush(stdout);
}

void executeCommand(char **tokens,char* executable)
{
    pid_t pid = fork();
    char cwd[4096];

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

            if (getcwd(cwd, sizeof(cwd)) != NULL) 
            {
                fprintf(stderr, "%s: No such file or directory\n", executable);
                exit(1);
            }
            fprintf(stderr, "%s: No such file or directory\n", tokens[0]);
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

