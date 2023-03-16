/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:37 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:40:51 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_pipes(t_cmdline *tree_node, t_redirection *red)
{
	if (tree_node->next != NULL && tree_node->outfile == 0)
	{
		pipe(red->pipe_fd);
		red->fd_out = red->pipe_fd[1];
		red->fd_in = red->pipe_fd[0];
	}
	dup2(red->fd_out, STDOUT_FILENO);
	close(red->fd_out);
	red->fd_out = red->tmp_out;
}
