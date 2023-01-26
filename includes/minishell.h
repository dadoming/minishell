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
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "my_lib.h"
#include "colors.h"

typedef struct s_list t_list;

//int g_exit_status;

#define REDIRECT "|<>"

enum quotes_e 
{
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    NO_QUOTE
};

enum bool_e 
{
    FALSE, 
    TRUE
};

/* Located in my_lib.h
typedef struct s_list
{
    char            *token;
    int             type;
    struct s_list   *next;
} t_list;
*/

typedef struct s_core
{
    char            **env_p;
    char            **execution_path;
    char            *free_line;
    char            *prompt;
    char            *logname;
} t_core;

typedef struct shell_s
{
    t_core          *core;
    t_list          *arg_list;
    int             signalset;
    void            (*SIGINT_handler)(int);
} shell_t;

/* main.c */
void	free_list(t_list **lst);
void    clear_looped_values(shell_t *mini);

/* prompt.c */
void    prompt(shell_t *mini);

/* init.c */
int     init(shell_t **mini, char **envp);

/* evaluate.c */
int     evaluate(shell_t *mini);

/* expander.c */
void    expander(shell_t *mini);
int     check_quote(int *active_quote, char c);

/* expand_env.c */
char    *expand_environment(char **content, shell_t *mini);

/* expand_repplace.c */
char    *replace(char **if_this_has, char *this, char *str_to_replace, int active_quote);

/* env_utils.c */
char    *get_env(char **env, char *var_name);

/* executor.c */
int     executor(shell_t *mini);

/* quotes.c */
int     quotes(shell_t *mini);

/* signals.c */
void    ignore_signal_for_shell();

/* helper_print.c */
void    print_quote_value(int single_q, int double_q, int word_amount);
void    helper_print(shell_t *mini);
void    print_node(void *s);

/* lexer.c */
void    lexer(char *rl_buffer, shell_t *mini);
int     check_for_ending_delimiter(char *buffer, char delimiter);

/* close_program.c */
void    close_program(shell_t *mini);

/* built_ins/ */
int     echo(t_list *arg_list);
void    pwd(void);
char    **export(t_list *lst, char **env_p);
char    **unset(t_list *lst, char **env);
void    env(char **env_p, int option);
void    cd(t_list *lst, char **env);

#endif
