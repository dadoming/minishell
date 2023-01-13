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

#include "my_lib.h"
#include "colors.h"

typedef struct s_list t_list;

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

enum controller_e
{
    COMMAND,
    DOLLAR,
    PIPE,
    REDIRECT_INPUT,
    REDIRECT_OUTPUT
};

typedef struct s_core
{
    char            **env_p;
    char            *rl_returned;
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
shell_t *mini(void);
void	free_list(t_list **lst);
void clear_looped_values(void);

/* prompt.c */
void prompt();

/* init.c */
int init(char **envp);

/* evaluate.c */
int evaluate();

/* expander.c */
void expander(void);
int check_quote(int *active_quote, char c);

/* expand_env.c */
char *expand_environment(char **content);

/* signals.c */
void ignore_signal_for_shell();

/* helper_print.c */
void print_quote_value(int single_q, int double_q, int word_amount);
void helper_print();
void print_node(void *s);

/* lexer.c */
void lexer(char *rl_buffer);
int check_for_ending_delimiter(char *buffer, char delimiter);

/* close_program.c */
void close_program(void);

#endif
