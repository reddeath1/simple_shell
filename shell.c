#include "shell.h"
/**
 * main - Main function
 * @argc: Number of arguments
 * @a: pointer to array arguments
 * @evn: Pointer to enviroment variable arrays
 * Return: (Always 0)
 */

int main(int argc, char **a, char **env)
{
        int count = 0;
        char buff = NULL, **cmd = NULL;
        size_t  buffer_size = 0;
        ssize_t chars = 0;
        (void) argc;

        while(1)
        {
                count++;
                prompter();
        }
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


/**
 * exec - function to execute the commands
 * @command: arg command to execute
 * @program: program to run
 */
void exec(char *command, char *program) 
{
	pid_t pid = fork();

	if (pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}else if (pid == 0)
	{
		if (execlp(command, command, NULL) == -1) 
		{
			fprintf(stderr, "%s: 1: %s: not found\n", programName, command);
			exit(EXIT_FAILURE);
		}
	} else 
	{
	       	int status;
		waitpid(pid, &status, 0);
	}
}


