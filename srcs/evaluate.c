/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:44:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:50:30 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

//print_tree(mini->cmdline);
int	evaluate(t_shell *mini)
{
	if (_length(rl_line_buffer) > 0)
	{
		add_history(rl_line_buffer);
		if (lexer(rl_line_buffer, mini) == 1)
			return (1);
		define_type(mini);
		if (expander(mini) == 1)
			return (1);
		if (quotes(mini) == TRUE)
			return (1);
		if (list()->_size(mini->arg_list) > 0)
		{
			if (build_ast(mini->arg_list, mini) == 1)
			{
				g_exit_status = 1;
				_putstring_n_fd("The first word needs to be a command", 2);
				return (1);
			}
		}
		return (0);
	}
	g_exit_status = 0;
	return (1);
}
