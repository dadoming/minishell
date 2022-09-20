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

#include "../includes/variables.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../includes/colors.h"

# define TRUE 1
# define FALSE 0

typedef struct variables_s
{
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
char *get_var_from_envp(char *envv, char prelimiter, char delimiter);



#endif