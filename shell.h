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

void prompter(void);
void run(char **tokens, char *input, char **env, int counts);
void exec(char **tokens, char *input, char **env, int counts);
int s_chdir(char **tokens);
char **tokenizeInput(char *buffer, const char *s);
int s_atoi(char *str);
int isExitCommand(char *command);
ssize_t sgetline(char **lineptr, size_t *n);
size_t strlength(const char *str);
void freemem(char **tokens);
char *strcopy(char *dest, char *src);
void EndOfFile(char *input);
void _write(int fn, const void * buf, size_t byte);
int str_compare(const char *str1, const char *str2);
void signal_handler(int signals);
void freexit(char **tokens);
void print_error(char *name, int counts, char **tokens);
void display_env(char **env);
char **get_PATH(char **env);
char *str_concat(char *destination, const char *source);

#endif /* _SHELL_H_ */
