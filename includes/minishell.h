#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "variables.h"
#include "my_lib.h"
#include "../gnl/get_next_line.h"
#include "colors.h"

# define TRUE 1
# define FALSE 0

typedef struct variables_s
{
    char** env_p;

    char *logname;
    char *session_manager_name;
    char *path;
    char *current_working_directory;

} variables_t;

typedef struct sh_s
{
    variables_t *var;

} sh_t;


sh_t *mini(void);
int init(char **envp);



#endif