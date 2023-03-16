/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:12:33 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:14:04 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;
static void	execution(t_shell *mini, t_cmdline *aux, char *command, int i);
int			cmd_is_directory(char *cmd);
static int	filepath_is_accessible(t_shell *mini, t_cmdline *aux, int i);

void	execute_command(t_shell *mini, t_cmdline *aux, int i)
{
	char	*command;
	char	**path;

	if (filepath_is_accessible(mini, aux, i) == 1)
		return ;
	path = find_path(mini->core->env_p);
	command = get_command(aux->cmd, path);
	if (command != NULL && command[0] == '/')
		execution(mini, aux, command, i);
	else if (_search(aux->cmd, '/') != 0 && command == NULL)
	{
		_putstring_fd("minishell: ", STDERR_FILENO);
		_putstring_fd(aux->cmd, STDERR_FILENO);
		_putstring_n_fd(": No such file or directory", STDERR_FILENO);
	}
	else
	{
		_putstring_fd("minishell: ", STDERR_FILENO);
		_putstring_fd(aux->cmd, STDERR_FILENO);
		_putstring_n_fd(": command not found", STDERR_FILENO);
	}
	if (path)
		free_array(path);
	if (command)
		free(command);
}

static int	filepath_is_accessible(t_shell *mini, t_cmdline *aux, int i)
{
	if (cmd_is_directory(aux->cmd) == 1)
		return (1);
	else if (access(aux->cmd, X_OK) == 0 && (aux->cmd[0] == '.' \
		|| aux->cmd[0] == '/'))
	{
		execution(mini, aux, aux->cmd, i);
		return (1);
	}
	else if (access(aux->cmd, F_OK) == 0 && access(aux->cmd, X_OK) \
		!= 0 && (aux->cmd[0] == '.' || aux->cmd[0] == '/'))
	{
		_putstring_fd(aux->cmd, STDERR_FILENO);
		_putstring_n_fd(": Permission denied", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	cmd_is_directory(char *cmd)
{
	if (check()->_is_directory(cmd) == 1)
	{
		_putstring_fd("minishell: ", STDERR_FILENO);
		_putstring_fd(cmd, STDERR_FILENO);
		_putstring_n_fd(": is a directory", STDERR_FILENO);
		g_exit_status = 126;
		return (1);
	}
	return (0);
}

static void	execution(t_shell *mini, t_cmdline *aux, char *command, int i)
{
	mini->pid[i] = fork();
	if (mini->pid[i] == 0)
	{
		execve(command, aux->arg, mini->core->env_p);
		print_normal_error(command);
		g_exit_status = 127;
		exit(127);
	}
	else
	{
		signal(SIGINT, sig_block_c);
	}
}
