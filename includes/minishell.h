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
    char            *home;
} t_core;

typedef struct s_redirection
{
    int             tmp_in;
    int             tmp_out;
    int             fd_in;
    int             fd_out;

    int             pipe_fd[2];
} t_redirection;

typedef struct s_cmdline
{
    char                **outfile;
    char                **infile;
    char                *cmd;
    char                **arg;
    struct s_cmdline    *next;
} t_cmdline;

typedef struct shell_s
{
    void            (*SIGINT_handler)(int);
    int             signalset;

    int             here_doc;
    pid_t           *pid;
    int             clear_pid;
    int             child_num;

    int             sigterminate;

    t_list          *arg_list;
    t_core          *core;
    t_cmdline       *cmdline;
} shell_t;

shell_t *m(void);

void	free_list(t_list **lst);
void    clear_looped_values(shell_t *mini);

void    prompt(shell_t *mini);
int     init(shell_t **mini, char **envp);

int     evaluate(shell_t *mini);


int    lexer(char *rl_buffer, shell_t *mini);
int     check_for_ending_delimiter(char *buffer, char delimiter);
int has_redir(shell_t *mini, int quote, int i, t_list *aux);
int     do_in_out_sep(t_list **lst, char *str, t_list *aux, int i, char redir_sign);
int next_node_is_redirect(char *next_node_str);
void redirect_at_beggining(char *str, int i, t_list **lst, t_list *aux);
void redirect_at_middle_or_end(char *str, int i, t_list **lst, t_list *aux);


int     expander(shell_t *mini);
int     check_quote(int *active_quote, char c);

void define_type(shell_t *mini);


int expand_environment(char **content, shell_t *mini, int *active_quote, char *variable, int curr_pos);

char    *replace(char **if_this_has, char *this, char *str_to_replace, int active_quote, int i);

char    *get_env(char **env, char *var_name);

int     quotes(shell_t *mini);
void remove_quote_if_quote_found(int *outer_quote, char *str, int *location, int *i);
void no_quote_quote_found(int *outer_quote, char quote, int *location, int *i);
char *remove_quotes(char *str, char c, int i);
void assign_outer_quote(char c, int *outer_quote, int *quote_amount);

int build_ast(t_list *lst, shell_t *mini);
void print_tree(t_cmdline *cmdline);

int executor(shell_t *mini, t_cmdline *aux);
int execute_process(shell_t *mini, t_cmdline *cmdline, int child_num);
char    **find_path(char **env);
void    free_path(char **path);
char	*get_command(char *command, char **path);
void	close_pipes(shell_t *mini);

// TODAY
void parse_outfile(t_cmdline *tree_node, t_redirection *red);
int parse_infile(shell_t *mini, t_cmdline *cmdtree, t_redirection *red);
t_cmdline *get_redir(t_list *arg_list, t_cmdline *tree_node);
void parse_pipes(t_cmdline *tree_node, t_redirection *red);
void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i);
void finish_execution(t_redirection *red);
int	heredoc(char *eof, shell_t *mini);
void fun_exit(char **arg);
int file_err_heredoc(char **infile, int len, shell_t *mini, t_redirection *red);
void print_error(char *identifier);
void free_array(char **array);
void sig_block_c(int signo);
void sigint_handler(int signum);
void sigquit_handler(int signum);
void sigterm_handler(int signum);
void sig_block(int signo);


int is_built_in(t_cmdline *cmdline, shell_t *mini);
int     echo(char **args);
void    pwd(void);
char    **export(char **arg, char **env_p);
char **unset(char **arg, char **env);
void    env(char **env_p, int option);
char **    cd(char **arg, char **env, shell_t *mini);
void    close_program(shell_t *mini);

char	*my_getenv(const char *name, char **env);
int	set_env_var(char **my_env, const char *var_name, const char *new_value);
char     **set_var(char **env_p, char *var_name, char *var_value);


void print_normal_error(char *error);
void print_syntax_error(char c);


void    ignore_signal_for_shell();

void    print_quote_value(int single_q, int double_q, int word_amount);
void    helper_print(t_list *lst);
void    print_node(void *s);



#endif
