/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:40:57 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:41:20 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	reset_fds(t_redirection *red)
{
	dup2(red->tmp_in, STDIN_FILENO);
	dup2(red->tmp_out, STDOUT_FILENO);
	close(red->tmp_in);
	close(red->tmp_out);
}
