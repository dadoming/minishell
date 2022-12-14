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



enum quotes_e {
    SINGLE_QUOTE,
    DOUBLE_QUOTE,
    NO_QUOTE
};

enum bool_e {
    FALSE, 
    TRUE
};

typedef struct shell_s
{
    t_list          *arg_list;
    char            *prompt;
    char            *out;
    char            **arg_v;
    int             arg_c;
    char            **env_p;
    char            *logname;
    char            *cwd;
    //built_in_t    built_in[6];
    int             signalset;
    void            (*SIGINT_handler)(int);
} shell_t;

/* main.c */
shell_t *mini(void);

/* prompt.c */
void get_input();

/* init.c */
int init(char **envp);

/* signals.c */
void ignore_signal_for_shell();

/* helper_print.c */
void print_quote_value(int single_q, int double_q, int word_amount);
void helper_print();
void print_node(void *s);

/* parser/ */
t_list *load_input(char **trimmed, t_list *arguments);
int delimiter_found(char c);
void trim_string(char *str, char ***trimmed);
t_list *take_input(char *rl_buffer);
void check_qs(char *rl_buffer, int *single_q, int *double_q, int *word_amount);
int check_for_ending_quote(char *rl_buffer, char delimiter);

#endif
