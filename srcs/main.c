/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:37:02 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 19:06:59 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_shell	*mini;

	(void)argv;
	if (argc != 1)
		return (printf("Wrong Input. Enter ./minishell\n"));
	if (init(&mini, envp) == TRUE)
	{
		while (1)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, sigint_handler);
			signal(SIGTERM, sigterm_handler);
			prompt(mini);
			if (evaluate(mini) == 1)
			{
				clear_looped_values(&mini);
				continue ;
			}
			if (executor(mini, mini->cmdline) == 1)
				break ;
			clear_looped_values(&mini);
		}
	}
	close_program(&mini);
	return (0);
}
