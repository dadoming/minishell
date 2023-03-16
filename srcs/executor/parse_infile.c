/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:22:30 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:18:09 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static int	treat_infile(t_redirection *red, t_shell *mini, \
	int i, int fd);
int			check_for_heredoc(t_shell *mini, int last_position, \
	t_redirection *red, int fd);
void		helper_norm2(t_cmdline *cmdtree, int i, \
	int heredoc_value, int fd);

int	parse_infile(t_shell *mini, t_cmdline *cmdtree, t_redirection *red)
{
	if (cmdtree->infile != NULL)
	{
		red->fd_in = treat_infile(red, mini, -1, 0);
		if (red->fd_in == -1)
		{
			cmdtree = cmdtree->next;
			if (cmdtree != NULL)
				executor(mini, cmdtree);
			return (-1);
		}
	}
	dup2(red->fd_in, STDIN_FILENO);
	close(red->fd_in);
	red->fd_in = red->tmp_in;
	return (0);
}

int	open_file(int fd, int i, t_shell *mini)
{
	if (fd > 0)
		close(fd);
	fd = open(mini->cmdline->infile[i + 1], O_RDONLY);
	g_exit_status = 1;
	return (fd);
}

static int	treat_infile(t_redirection *red, t_shell *mini, int i, int fd)
{
	int	heredoc_value;
	int	store_last_i_value;

	heredoc_value = 0;
	store_last_i_value = 0;
	while (mini->cmdline->infile[++i] != 0)
	{
		store_last_i_value = i;
		if (mini->cmdline->infile[i][0] == '<' && \
			mini->cmdline->infile[i][1] == '\0')
		{
			fd = open_file(fd, i, mini);
			if (fd == -1)
			{
				heredoc_value = file_err_heredoc(mini->cmdline->infile, \
					_array_length(mini->cmdline->infile) - 1, mini, red);
				break ;
			}
		}
	}
	if (heredoc_value != 1 && fd != -1)
		fd = check_for_heredoc(mini, store_last_i_value, red, fd);
	helper_norm2(mini->cmdline, i, heredoc_value, fd);
	return (fd);
}

void	helper_norm2(t_cmdline *cmdtree, int i, int heredoc_value, int fd)
{
	if (fd == -1 && heredoc_value != 1)
	{
		print_normal_error(cmdtree->infile[i + 1]);
	}
	else if (heredoc_value == 1)
	{
		_putstring_fd("minishell: ", 2);
		_putstring_fd(cmdtree->infile[i + 1], 2);
		_putstring_fd(": ", 2);
		_putstring_n_fd("No such file or directory", 2);
	}
}
