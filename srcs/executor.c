/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:42:00 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 19:56:00 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

// Just to not give a valgrind error -.-
void	init_(t_shell *mini, t_redirection *red)
{
	int	i;

	i = 0;
	mini->pid = malloc(sizeof(int) * (mini->child_num + 1));
	mini->clear_pid = 1;
	while (i < mini->child_num + 1)
	{
		mini->pid[i] = 0;
		i++;
	}
	red->tmp_in = dup(STDIN_FILENO);
	red->tmp_out = dup(STDOUT_FILENO);
	red->fd_in = dup(red->tmp_in);
	red->fd_out = dup(red->tmp_out);
}

int	executor(t_shell *mini, t_cmdline *aux)
{
	t_redirection	red;
	int				i;

	i = 0;
	init_(mini, &red);
	while (aux != NULL && i <= mini->child_num)
	{
		if (parse_infile(mini, aux, &red) == -1)
			return (0);
		parse_pipes(aux, &red, mini, i);
		parse_outfile(aux, &red);
		if (red.fd_out == -1)
			break ;
		if (is_built_in(aux, mini, i) == 1)
		{
			aux = aux->next;
			i++;
			continue ;
		}
		execute_command(mini, aux, i);
		aux = aux->next;
		i++;
	}
	wait_for_child(&red, &mini);
	return (0);
}
