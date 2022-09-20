#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "../includes/variables.h"
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"

# define TRUE 1
# define FALSE 0

typedef struct variables_s
{
    char *username;
    char *session_manager_name;
    char *path;

} variables_t;

typedef struct sh_s
{
    variables_t *var;

} sh_t;

sh_t *mini(void);
char *get_var_from_envp(char *envv, char prelimiter, char delimiter);



#endif