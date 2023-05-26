#include "shell.h"

/**
 * main - Main function
 * @argc: Number of command-line arguments
 * @argv: Array of command-line arguments
 * @env: Environmental variables
 * Return: Always 0
 */
int main(int argc, char *argv[], char **env)
{
	char *input = NULL;
	char **tokens = NULL;
	int numTokens = 0;
	int counts = 0;
	int status = 0;
	size_t input_size = 0;
	ssize_t read_bytes;
	(void)argc;

	while (1)
	{
		counts++;
		prompter();
		signal(SIGINT, signal_handler);
		read_bytes = sgetline(&input, &input_size);
		
		if (read_bytes == -1)
		{
			break;
		}

		run(tokens, argv[0], env, counts);

		if (read_bytes == EOF)
		{
			EndOfFile(input);
		}
		if (*input == '\n')
			free(input);
		else
		{
			input[strcspn(input, "\n")] = '\0';
			tokens = tokenizeInput(input, " \0");
			free(input);

			if (numTokens == -1)
				break;

			if (str_compare(tokens[0], "env") != 0)
				display_env(env);
			else if (isExitCommand(tokens[0]))
			{
				if (numTokens > 1)
				{
					status = s_atoi(tokens[1]);

					exit(status);
				}
				else
				{
					free(input);
					exit(EXIT_SUCCESS);
				}
			}
			else if (str_compare(tokens[0], "cd") != 0)
				s_chdir(tokens);
			else
				run(tokens, argv[0], env, counts);
		}
		fflush(stdin);
		input = NULL;
		input_size = 0;
	}

	return (EXIT_SUCCESS);
}

/**
 * signal_handler - Signal handler for interrupt signals
 * @signals: Signal number
 * Description: This function handles interrupt signals and prints a prompt
 * for the shell.
 */
void signal_handler(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\nShell>> ", 14);
}

/**
 * prompter - function to display prompts
 * Return: always null
 */
void prompter(void)
{
	write(STDOUT_FILENO, "Shell>> ", 500);
}

/**
 * tokenizeInput - Function to tokenize input string
 * @input: Input string
 * @delimiters: Delimiters used for tokenization
 * Return: Array of tokens
 */

char **tokenizeInput(char *input, const char *delimiters)
{
	char *token = NULL, **tokens = NULL;
	size_t input_size = 0;
	int i = 0;

	if (input == NULL)
		return (NULL);

	input_size = strlength(input);
	tokens = malloc((input_size + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("Unable to allocate memory!");
		free(input);
		freemem(tokens);
		exit(EXIT_FAILURE);
	}

	token = strtok(input, delimiters);
	while (token != NULL)
	{
		tokens[i] = malloc(s_strlen(token) + 1);
		if (tokens[i] == NULL)
		{
			perror("Unable to allocate memory!!");
			freemem(tokens);
			return (NULL);
		}
		strcopy(tokens[i], token);
		token = strtok(NULL, delimiters);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
