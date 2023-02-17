#ifndef MINISHELL_H
#define MINISHELL_H

//#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
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

enum redirection_e 
{
    WORD,           // command or argument
    RED_INPUT,      // < sign
    HERE_DOC,       // << sign
    RED_OUTPUT,     // > sign
    APPEND_OUTPUT,  // >> sign
    INFILE,         // after <
    OUTFILE,        // after >
    DELIMITOR,      // after << aka EOF
    OUTFILE_APND,   // after >> 
    PIPE            // | sign
};

typedef struct s_core
{
    char            **env_p;
    char            *free_line;
    char            *prompt;
    char            *logname;
} t_core;

typedef struct s_cmdline
{
    int                 cmd_type;
    char                *cmd;
    char                **arg;
    struct s_cmdline    *next;
} t_cmdline;

typedef struct shell_s
{
    void            (*SIGINT_handler)(int);
    int             signalset;

    int             num_of_cmds;
    int             num_of_pipes;
    int             *fd;
    pid_t             pid;

    t_list          *arg_list;
    t_core          *core;
    t_cmdline       *cmdline;
} shell_t;

/* 
    main.c 
*/
void	free_list(t_list **lst);
void    clear_looped_values(shell_t *mini);

/* 
    prompt.c

    Prints a prompt and reads input from user. 
*/
void    prompt(shell_t *mini);

/* 
    init.c
    
    Initializes minishell's initial values
*/
int     init(shell_t **mini, char **envp);

/* 
   evaluate.c 

   This is the core of how the program treats the input. 
   1. add_history(): Add input to history if any was passed.
   2. lexer(): It will get all the words passed and store them in a linked list.
   3. expander(): Will expand all $ values outside single quotes.
   4. quotes(): Will remove all quotes to be removed.
*/
int     evaluate(shell_t *mini);

/* 
    lexer.c

    Produce tokens accordingly with the quotes and spaces provided in the input. 
*/
int    lexer(char *rl_buffer, shell_t *mini);
int     check_for_ending_delimiter(char *buffer, char delimiter);
int has_redir(shell_t *mini, int quote, int i, t_list *aux);
int     do_in_out_sep(t_list **lst, char *str, t_list *aux, int i, char redir_sign);
int next_node_is_redirect(char *next_node_str);
void redirect_at_beggining(char *str, int i, t_list **lst, t_list *aux);
void redirect_at_middle_or_end(char *str, int i, t_list **lst, t_list *aux);

/* 
    expander.c

    Iterate through the linked list and expand all $ values outside single quotes. 
*/
int     expander(shell_t *mini);
int     check_quote(int *active_quote, char c);

/*
    define_type.c

    Defines the type of the command.
*/
void define_type(shell_t *mini);

/* 
    expand_env.c
    
    This is the function that will make all the expansions.
    It checks if the variable exists in the environment and if it does, it will replace and return it.
*/
int expand_environment(char **content, shell_t *mini, int *active_quote, char *variable, int curr_pos);

/* 
    expand_replace.c

    Replace function. Returns the new string with the replaced value dynamically allocated.
*/
char    *replace(char **if_this_has, char *this, char *str_to_replace, int active_quote, int i);

/* 
    env_utils.c 
    
    If env has value then return value else return NULL. 
    Example: get_env(env, "PATH")
*/
char    *get_env(char **env, char *var_name);

/*
    quotes.c

    Removes all quotes that are to be removed the same way bash does.
*/
int     quotes(shell_t *mini);
void remove_quote_if_quote_found(int *outer_quote, char *str, int *location, int *i);
void no_quote_quote_found(int *outer_quote, char quote, int *location, int *i);
char *remove_quotes(char *str, char c, int i);
void assign_outer_quote(char c, int *outer_quote, int *quote_amount);

/*
    build_ast.c
*/
void build_ast(t_list *lst, shell_t *mini);
void print_tree(t_cmdline *cmdline);

/* 
    executor.c 

    Executes the command.
*/
int     executor(shell_t *mini);
int execute_process(shell_t *mini, t_cmdline *cmdline, int child_num);
char    **find_path(char **env);
void    free_path(char **path);
char	*get_command(char *command, char **path);
void	close_pipes(shell_t *mini);

/* 
    built_ins/

    All the built in functions.
*/
int     echo(char **args);
void    pwd(void);
char    **export(char **arg, char **env_p);
char **unset(char **arg, char **env);
void    env(char **env_p, int option);
void    cd(t_list *lst, char **env);

/*
    close_program.c

    Frees all the memory and closes the program.
*/
void    close_program(shell_t *mini);

/* 
    print_error.c

    Prints a minishell error message. (maybe needs some tweaking)
*/
void print_error(char *command, char c);

/* signals.c */
void    ignore_signal_for_shell();

/* helper_print.c */
void    print_quote_value(int single_q, int double_q, int word_amount);
void    helper_print(t_list *lst);
void    print_node(void *s);



#endif
