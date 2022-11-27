#ifndef MINISHELL_H
#define MINISHELL_H

//#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "variables.h"
#include "my_lib.h"
#include "colors.h"

# define TRUE 1
# define FALSE 0

typedef struct built_in_s
{
    char *command;
    int (*echo)(char *arg, int option); // has option to not output newline 
    int (*cd)(char *path); // has to check if path exists in current folder / if it is absolute path and exists 
    int (*pwd)(char *arg); // print current working directory
    int (*export)(char *arg); // insert variable to env_p
    int (*unset)(char *arg); // remove variable from env_p
    int (*env)(char *arg); // only executes, printing the env_p
    int (*exit)(char *arg); // exits program with or without status
} built_in_t;

typedef struct variables_s
{
    char    **env_p;
    char    *logname;
    char    *cwd;

} variables_t;

typedef struct sh_s
{
    variables_t var;
    int         arg_c;
    char**      arg_v;
    built_in_t  built_in[6];
    
    int signalset;
    void   (*SIGINT_handler)(int);

} sh_t;


sh_t *mini(void);
int init(char **envp);

/* prompt.c */
void print_prompt();

/* init.c */
int init(char **envp);

void change_d(void);
void close_program(void);
int check_input(int argc, char** argv);

/* input_separator.c */
int parse_input(char *buffer);
void ignore_signal_for_shell();

#endif
