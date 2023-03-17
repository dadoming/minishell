/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:57 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 14:43:56 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	wait_for_child(t_redirection *red, t_shell **mini)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	if ((*mini)->clear_pid == 0)
		return ;
	while (i < (*mini)->child_num + 1)
	{
		waitpid((*mini)->pid[i], &status, 0);
		i++;
	}
	(*mini)->child_num = 0;
	free((*mini)->pid);
	(*mini)->clear_pid = 0;
	//if (WIFEXITED(status))
	//	g_exit_status = WEXITSTATUS(status);
	dup2(red->tmp_in, STDIN_FILENO);
	dup2(red->tmp_out, STDOUT_FILENO);
	close(red->tmp_in);
	close(red->tmp_out);
}
