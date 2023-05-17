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
