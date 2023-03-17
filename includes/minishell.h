/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:54:56 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 14:42:17 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <time.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/my_lib/my_lib.h"
# include "colors.h"

typedef struct s_list	t_list;

enum e_quotes
{
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	NO_QUOTE
};

enum e_bool
{
	FALSE,
	TRUE
};

enum e_redirection
{
	WORD,
	RED_INPUT,
	HERE_DOC,
	RED_OUTPUT,
	APPEND_OUTPUT,
	INFILE,
	OUTFILE,
	DELIMITOR,
	OUTFILE_APND,
	PIPE
};
typedef struct s_core
{
	char	*free_line;
	char	*prompt;
	char	*logname;
	char	*home;
	char	**env_p;
}	t_core;

typedef struct s_redirection
{
	int					tmp_in;
	int					tmp_out;
	int					fd_in;
	int					fd_out;
	int					pipe_fd[2];
}	t_redirection;

typedef struct s_cmdline
{
	char				**outfile;
	char				**infile;
	char				*cmd;
	char				**arg;
	struct s_cmdline	*next;
}	t_cmdline;

typedef struct s_norm
{
	int					i;		
	int					env_len;
	int					var_len;
	char				*env_variable;
	char				*env_value;
}	t_norm;

typedef struct s_shell
{
	int					here_doc;
	int					curr_pos;
	int					clear_pid;
	int					child_num;
	pid_t				*pid;
	t_list				*arg_list;
	t_core				*core;
	t_cmdline			*cmdline;
}	t_shell;

void		remove_word(char *str, int start, int end);
void		fix_expanded_values(t_shell *mini, int quote);
void		remove_quote_if_quote_found(int *outer_quote, \
	char *str, int *location, int *i);
void		no_quote_quote_found(int *outer_quote, \
	char quote, int *location, int *i);
char		**add_to_end_of_env(char **env_p, \
	char *var_name, char *var_value);
void		substitute_env_var(char **env_p, \
	char *var_name, char *var_value);
char		*remove_non_existent(t_shell *mini, \
	char *content, int quote, int i);
char		*remove_unexistent(char *str, int quote, int end, int start);
void		free_list(t_list **lst);
void		clear_looped_values(t_shell **mini);
void		prompt(t_shell *mini);
void		env(char **env_p, int option);
void		redirect_at_beggining(char *str, int i, t_list **lst, t_list *aux);
void		redirect_at_middle_or_end(char *str, int i, \
	t_list **lst, t_list *aux);
void		define_type(t_shell *mini);
void		no_quote_quote_found(int *outer_quote, \
	char quote, int *location, int *i);
void		assign_outer_quote(char c, int *outer_quote, int *quote_amount);
void		print_tree(t_cmdline *cmdline);
void		free_tree(t_shell **mini);
void		wait_for_child(t_redirection *red, t_shell **mini);
void		parse_outfile(t_cmdline *tree_node, t_redirection *red);
void		parse_pipes(t_cmdline *tree_node, t_redirection *red, t_shell *mini, int i);
void		execute_command(t_shell *mini, t_cmdline *aux, int i);
void		fun_exit(t_shell *mini, char **arg);
void		print_error(char *identifier);
void		free_array(char **array);
void		sig_block_c(int signo);
void		sigint_handler(int signum);
void		sigquit_handler(int signum);
void		sigterm_handler(int signum);
void		print_normal_error(char *error);
void		print_syntax_error(char c);
void		helper_print(t_list *lst);
void		print_node(void *s);
void		pwd(void);
void		close_program(t_shell **mini);
int			quotes(t_shell *mini);
int			only_one_quote(char *input);
char		*treat_quotes(char *str);
int			calculate_size(char **if_this_has, char *this, \
	char *str_to_replace, int active_quote);
int			do_the_replace(t_norm norm, t_shell *mini, \
	char **content, int *active_quote);
int			normal_expand(t_shell *mini, char **content, \
	int *active_quote, char *variable);
int			expand_status(char **content, char *variable, \
	int *active_quote, int curr_pos);
int			expand_double_dollar(char **content, int *active_quote, \
	char *variable, int curr_pos);
int			next_dollar_position(char *content, int *quote, int curr_pos);
int			init(t_shell **mini, char **envp);
int			evaluate(t_shell *mini);
int			lexer(char *rl_buffer, t_shell *mini);
int			check_for_ending_delimiter(char *buffer, char delimiter);
int			has_redir(int quote, int i, t_list *aux);
int			next_node_is_redirect(char *next_node_str);
int			expander(t_shell *mini);
int			check_quote(int *active_quote, char c);
int			expand_environment(char **content, \
	t_shell *mini, int *active_quote, char *variable);
int			quotes(t_shell *mini);
int			build_ast(t_list *lst, t_shell *mini);
int			executor(t_shell *mini, t_cmdline *aux);
int			execute_process(t_shell *mini, t_cmdline *cmdline, int child_num);
int			parse_infile(t_shell *mini, t_cmdline *cmdtree, t_redirection *red);
int			heredoc(char *eof, t_shell *mini);
int			file_err_heredoc(char **infile, int len, \
	t_shell *mini, t_redirection *red);
int			check_for_heredoc(t_shell *mini, int last_position, \
	t_redirection *red, int fd);
int			is_built_in(t_cmdline *cmdline, t_shell *mini);
int			echo(char **args);
char		*replace(char **if_this_has, char *this, char *str_to_replace);
char		*get_env(char **env, char *var_name);
char		*remove_quotes(char *str, char c, int i);
char		*get_command(char *command, char **path);
char		*my_getenv(const char *name, char **env);
t_cmdline	*get_redir(t_list *arg_list, t_cmdline *tree_node);
char		**find_path(char **env);
char		**find_path(char **env);
char		**export(char **arg, char **env_p);
char		**unset(char **arg, char **env);
char		**cd(char **arg, char **env, t_shell *mini);
char		**set_var(char **env_p, char *var_name, char *var_value);

#endif
