/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:29:50 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 22:29:51 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_prompt(t_shell *mini);

/* Prints a prompt and reads input from user. */
void	prompt(t_shell *mini)
{
	print_prompt(mini);
	mini->core->free_line = readline(mini->core->prompt);
	if (!mini->core->free_line)
		fun_exit(mini, NULL);
}

static void	print_prompt(t_shell *mini)
{
	mini->core->logname = my_getenv("LOGNAME", mini->core->env_p);
	if (mini->core->logname != NULL)
	{
		mini->core->prompt = string()->_duplicate(BMAG);
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, mini->core->logname);
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, COLOR_RESET);
		mini->core->prompt = string()->_append(&mini->core->prompt, " > ");
		mini->core->prompt = string()->_append(&mini->core->prompt, BRED);
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, "minishell");
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, "\e[1;33m$\e[0m ");
	}
	else
	{
		mini->core->prompt = string()->_duplicate(BRED);
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, "minishell");
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, COLOR_RESET);
		mini->core->prompt = string()-> \
			_append(&mini->core->prompt, "\e[1;33m$\e[0m ");
	}
}
