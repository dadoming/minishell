/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:01:29 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 21:42:46 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_for_letter(char *str);
static int	too_many_args(char **arg);
extern int	g_exit_status;

void	fun_exit(t_shell *mini, char **arg, t_cmdline *cmdline, int i)
{
	int	status;

	status = 0;
	printf("exit\n");
	if (too_many_args(arg))
		return ;
	if (arg != NULL && arg[1])
		status = string()->_atoi(arg[1]);
	else
		status = 0;
	if (arg != NULL && !check_for_letter(arg[1]))
	{
		_putstring_fd("minishell: exit: ", 2);
		_putstring_fd(arg[1], 2);
		_putstring_n_fd(": numeric argument required", 2);
		close_program(&mini);
		exit(2);
	}
	else
	{
		close_program(&mini);
		exit(status);
	}
}

static int	check_for_letter(char *str)
{
	int	i;
	int	only_one;

	if (!str)
		return (1);
	only_one = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-' || str[i] == '+' )
		{
			only_one++;
			i++;
		}
		if (str[i] >= '0' && str[i] <= '9' && only_one <= 1)
			i++;
		else
			return (0);
	}
	return (1);
}

static int	too_many_args(char **arg)
{
	int	i;

	i = 0;
	if (arg != NULL)
	{
		while (arg[i] != 0)
			i++;
	}
	if (i > 2)
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 127;
		return (1);
	}
	return (0);
}
