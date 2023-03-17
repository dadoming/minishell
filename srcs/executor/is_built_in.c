/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:18:49 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 19:56:16 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	extra_built_in(t_cmdline *cmdline, t_shell *mini, int i)
{
	if (_same_word(cmdline->cmd, "unset", 5))
	{
		mini->core->env_p = unset(cmdline->arg, mini->core->env_p);
		return (1);
	}
	else if (_same_word(cmdline->cmd, "env", 3))
	{
		env(mini->core->env_p, 2);
		return (1);
	}
	else if (_same_word(cmdline->cmd, "exit", 4))
	{
		fun_exit(mini, cmdline->arg, cmdline, i);
		return (1);
	}
	return (0);
}

int	is_built_in(t_cmdline *cmdline, t_shell *mini, int i)
{
	if (_same_word(cmdline->cmd, "echo", 4))
	{
		echo(cmdline->arg);
		return (1);
	}
	else if (_same_word(cmdline->cmd, "pwd", 3))
	{
		pwd();
		return (1);
	}
	else if (_same_word(cmdline->cmd, "cd", 2))
	{
		mini->core->env_p = cd(cmdline->arg, mini->core->env_p, mini);
		return (1);
	}
	else if (_same_word(cmdline->cmd, "export", 6))
	{
		mini->core->env_p = export(cmdline->arg, mini->core->env_p);
		return (1);
	}
	if (extra_built_in(cmdline, mini, i))
		return (1);
	return (0);
}
