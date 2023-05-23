#include "shell.h"
/**
 * main - Main function
 * @argc: Number of arguments
 * @a: pointer to array arguments
 * @evn: Pointer to enviroment variable arrays
 * Return: (Always 0)
 */
int main (void) {
    char *input;
    char *tokens[MAX_TOKENS];
    int numTokens;
    ssize_t  bytes_read = 0;
    size_t input_size = 0;

    while (1) {
        prompter();

        bytes_read = _getline(&input, &input_size);

        if (bytes_read == -1) {
            // End of file (Ctrl+D) is encountered
            printf("\n");
            break;
        }

        // Tokenize input
        tokenizeInput(input, tokens, &numTokens);

        if (numTokens > 0) {
            if (strcmp(tokens[0], "alias") == 0) {
                executeAliasCommand(tokens);
            } else if (strcmp(tokens[0], "cd") == 0) {
                changeDirectory(tokens);
            } else if (isExitCommand(tokens[0])) {
                // Check for additional argument
                if (numTokens > 1) {
                    // Convert status argument to integer
                    int status = _atoi(tokens[1]);

                    // Exit the shell with status
                    exit(status);
                } else {
                    // Exit the shell without status
                    break;
                }
            } else {
                executeCommand(tokens);
            }
        }

        free(input);
    }

    return 0;
}

/**
 * prompter - funtion to display prompts
 * Return: always null
 */
void prompter (void)
{
        printf("Shell> ");
        fflush(stdout);
}

void executeCommand (char **tokens)
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
