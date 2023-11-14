#ifndef SHELL_H
#define SHELL_H

#define MAX_CMD_LEN 1024
#define MAX_ALIASES 100
#define MAX_ALIAS_LEN 100
#define MAX_COMMAND_LEN 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H

int execute_command(char *command);
void execmd(char **argv);
char *get_path(char *command);
char **parse_command(char *command, int *num_tokens);
void free_argv(char **argv);


#endif



#endif
