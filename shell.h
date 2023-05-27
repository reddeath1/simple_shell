#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define INPUT_READ_BUF_SIZE 1024
#define INPUT_WRITE_BUF_SIZE 1024
#define FLUSH_BUFFER -1
#define COMMAND_NORM	0
#define COMMAND_OR		1
#define COMMAND_AND		2
#define COMMAND_CHAIN	3
#define TO_LOWERCASE	1
#define TO_UNSIGNED	2
extern char **environ;
#define HISTORY_FILE	".history"
#define HISTORY_MAX	4096

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct detail - Structure representing program details
 * @arg: Argument string
 * @argv: Array of argument strings
 * @path: Path string
 * @argc: Number of arguments
 * @line_c: Line count
 * @err_num: Error number
 * @linecount_flag: Line count flag
 * @fname: File name
 * @env: Environmental variables list
 * @history: Command history list
 * @alias: Alias list
 * @envi: Array of environmental variables
 * @env_changed: Environmental variables changed flag
 * @status: Status code
 * @cmd_buf: Command buffer
 * @rfd: File descriptor
 * @cmd_buf_type: Command buffer type
 * @histcount: History count
*/
typedef struct detail
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_c;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **envi;
	int env_changed;
	int status;
	char **cmd_buf;
	int rfd;
	int cmd_buf_type;
	int histcount;
} details;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - Structure representing a built-in command.
 * @type: Command type (name)
 * @func: Pointer to the function that implements the command
 */
typedef struct builtin
{
	char *type;
	int (*func)(details *);
} builtins;

int hsh_loop(details *, char **);
int is_builtin(details *);
void find_cmd(details *);
void fork_cmd(details *);

int is_command(details *, char *);
char *char_duplicates(char *, int, int);
char *is_path(details *, char *, char *);

void error_put(char *str);
int error_putchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *s);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *str_locate(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void sfree(char **p);
void *_realloc(void *, unsigned int, unsigned int);

int pointer_free(void **addr);
int interact(details *);
int _delim(char, char *);
int _alpha(int);
int _atoi(char *);
int err_atoi(char *);
void perrors(details *p, char *er);
int display_decimal(int, int);
char *cn(long int nu, int _base, int flags);
void rm_comments(char *);

int myexit(details *);
int mycd(details *);
int myhelp(details *);

int myhistory(details *);
int myalias(details *);

ssize_t _input(details *);
int _getline(details *, char **, size_t *);
void Signals(int s);
void clearinfo(details *);
void setinfo(details *, char **);
void freeinfo(details *, int);

char *_getenv(details *, const char *);
int myenv(details *);
int mysetenv(details *);
int myunsetenv(details *);
int populate_env_list(details *);

char **get_environ(details *);
int _unsetenv(details *, char *);
int _setenv(details *, char *, char *);

char *get_history_file(details *info);
int write_history(details *info);
int read_history(details *info);
int build_history_list(details *info, char *buf, int linecount);
int renumber_history(details *info);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t display_list_string(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(details *, char *, size_t *);
void check_chain(details *, char *, size_t *, size_t, size_t);
int replace_alias(details *);
int replace_vars(details *);
int str_replace(char **, char *);

#endif
