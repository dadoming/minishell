/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:32:36 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 01:05:26 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	treat_outfile(t_cmdline *tree_node);

void	parse_outfile(t_cmdline *tree_node, t_redirection *red)
{
	if (tree_node->outfile != NULL)
	{
		red->fd_out = treat_outfile(tree_node);
		dup2(red->fd_out, STDOUT_FILENO);
		close(red->fd_out);
		red->fd_out = red->tmp_out;
	}
}

static int	open_file_trunc(int fd, int *extra, int i, t_cmdline *tree_node)
{
	if (*extra > 0)
		close(fd);
	fd = open(tree_node->outfile[i + 1], \
		O_WRONLY | O_CREAT | O_TRUNC, 0777);
	(*extra)++;
	return (fd);
}

static int	open_file_append(int fd, int *extra, int i, t_cmdline *tree_node)
{
	if (*extra > 0)
		close(fd);
	fd = open(tree_node->outfile[i + 1], \
		O_WRONLY | O_CREAT | O_APPEND, 0777);
	(*extra)++;
	return (fd);
}

static int	treat_outfile(t_cmdline *tree_node)
{
	int	i;
	int	extra;
	int	fd;

	extra = 0;
	i = 0;
	while (tree_node->outfile[i] != 0)
	{
		if (tree_node->outfile[i][0] == '>' && \
			tree_node->outfile[i][1] == '>' \
			&& tree_node->outfile[i][2] == '\0')
			fd = open_file_append(fd, &extra, i, tree_node);
		else if (tree_node->outfile[i][0] == '>' && \
			tree_node->outfile[i][1] == '\0')
			fd = open_file_trunc(fd, &extra, i, tree_node);
		i++;
	}
	return (fd);
}
