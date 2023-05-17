#ifndef _SHELL_H_
#define _SHELL_H
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>


int main(int ac, char **av, char **env);
void prompter();



#endif /* _SHELL_H_ */_
