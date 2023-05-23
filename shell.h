#ifndef _SHELL_H_
#define _SHELL_H_
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdarg.h> 

#define MAX_INPUT_SIZE 1024
#define MAX_TOKEN_SIZE 50
#define MAX_TOKENS 100
#define MAX_ALIAS_SIZE 100
#define MAX_ALIAS_NAME_SIZE 50
#define MAX_ALIAS_VALUE_SIZE 50
#define MAX_COMMAND_LENGTH 100

struct Alias
{
    char name[MAX_ALIAS_NAME_SIZE];
    char value[MAX_ALIAS_VALUE_SIZE];
};

struct Alias aliases[MAX_ALIAS_SIZE];
int numAliases = 0;

void prompter(void);
void displayAlias(const char *name);
void setAlias(const char *name, const char *value);
void changeDirectory(char **tokens);
void executeCommand(char **tokens);
void tokenizeInput(char *input, char **tokens, int *numTokens);
void executeAliasCommand(char **tokens);
int _atoi(char *str);
int isExitCommand(char *command);
ssize_t _getline(char **lineptr, size_t *n);

#endif /* _SHELL_H_ */
