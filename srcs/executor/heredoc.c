/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:14:27 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:18:31 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;
static int	helper_norm1(t_redirection *red);

int	check_for_heredoc(t_shell *mini, int last_position, \
	t_redirection *red, int fd)
{
	int	i;

	i = _array_length(mini->cmdline->infile) - 1;
	while (i >= 0)
	{
		if (mini->cmdline->infile[i][0] == '<' && mini->cmdline->infile[i][1] \
			== '<' && mini->cmdline->infile[i][2] == '\0')
		{
			if (i >= last_position - 1)
			{
				if (fd > 0)
					close(fd);
				heredoc(mini->cmdline->infile[i + 1], mini);
				fd = helper_norm1(red);
				break ;
			}
			else
			{
				heredoc(mini->cmdline->infile[i + 1], mini);
				break ;
			}
		}
		i--;
	}
	return (fd);
}

static int	helper_norm1(t_redirection *red)
{
	int	fd;

	fd = open(".heredoc_storer", O_RDONLY | O_ASYNC);
	g_exit_status = 1;
	if (fd == -1)
	{
		reset_fds(red);
		print_normal_error("heredoc");
		return (-1);
	}
	return (fd);
}

int	file_err_heredoc(char **infile, int len, t_shell *mini, t_redirection *red)
{
	int	fake_heredoc;

	reset_fds(red);
	fake_heredoc = 0;
	while (len >= 0)
	{
		if (infile[len][0] == '<' && infile[len][1] == '<' \
			&& infile[len][2] == '\0')
		{
			fake_heredoc = 1;
			heredoc(infile[len + 1], mini);
			break ;
		}
		len--;
	}
	return (fake_heredoc);
}

void	print_eof_error(char *eof)
{
	write(2, "minishell: ", 11);
	write(2, "warning: here-document delimited by end-of-file (wanted `", 58);
	write(2, eof, string()->_length(eof));
	write(2, "')\n", 3);
}

int	heredoc(char *eof, t_shell *mini)
{
	int		file;
	char	*buffer;

	file = open(".heredoc_storer", O_CREAT \
		| O_WRONLY | O_ASYNC | O_TRUNC, 0000644);
	if (file < 0)
		return (1);
	mini->here_doc = 1;
	while (1)
	{
		buffer = readline("> ");
		if (buffer)
			buffer = string()->_append(&buffer, "\n");
		if (!buffer)
			print_eof_error(eof);
		if ((_compare_n(eof, buffer, _length(eof)) == 0) || !buffer)
			break ;
		write(file, buffer, string()->_length(buffer));
		free(buffer);
	}
	free(buffer);
	close(file);
	return (0);
}
