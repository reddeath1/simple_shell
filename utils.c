#include "shell.h"

int s_atoi(char *str)
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

size_t s_strlen(const char *str)
{
        const char *s = str;
        while (*s)
                ++s;
        return s - str;
}

ssize_t _getline(char **lineptr, size_t *n)
{

    // Initialize variables
    ssize_t read_bytes = 0;
    size_t buffer_size = 0;
    char *buffer = NULL, *new_buffer = NULL;
    int c;
    char *line = NULL;
    ssize_t i = 0;
    size_t new_size = 0;

    if (lineptr == NULL || n == NULL)
    {
        return -1;
    }

    // Read characters until newline or end of file is encountered
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Reallocate buffer if necessary
        if (read_bytes >= (ssize_t)buffer_size)
        {
            new_size = buffer_size + 1; // Increase buffer size by 1
            new_buffer = realloc(buffer, new_size);
            if (new_buffer == NULL)
            {
                // Error occurred while reallocating memory
                free(buffer);
                return -1;
            }
            buffer = new_buffer;
            buffer_size = new_size;
        }

        // Store the character in the buffer
        buffer[read_bytes++] = c;
    }

    // Allocate memory for the line
    if (read_bytes > 0)
    {
        line = malloc(read_bytes + 1); // Add space for null terminator
        if (line == NULL)
        {
            // Error occurred while allocating memory
            free(buffer);
            return -1;
        }
        // Copy the characters from the buffer to the line
        for (; i < read_bytes; i++)
        {
            line[i] = buffer[i];
        }
        line[read_bytes] = '\0'; // Null-terminate the line
        *lineptr = line;
    }
    else
    {
        *lineptr = NULL; // No characters read, set lineptr to NULL
    }

    // Update the buffer size
    *n = buffer_size;

    // Free the buffer
    free(buffer);

    if (c == EOF)
    {
        // End of file is encountered
        return -1;
    }

    return read_bytes;
}


void s_chdir(char **tokens)
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
