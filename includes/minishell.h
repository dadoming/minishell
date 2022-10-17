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

typedef struct variables_s
{
    char    **env_p;
    char    *logname;
    char    *cwd;

} variables_t;

typedef struct sh_s
{
    variables_t var;
    int         argcount;
    char**      argvalue;
    
    int signalset;
    void   (*SIGINT_handler)(int);

} sh_t;


sh_t *mini(void);
int init(char **envp);

/* prompt.c */
void print_prompt();



#endif
