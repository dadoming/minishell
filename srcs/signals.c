/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:26:21 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 22:35:45 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_exit_status;

void	sig_block_c(int signo)
{
	(void)signo;
	signal(SIGINT, SIG_IGN);
	g_exit_status = 130;
	_putchar_fd('\n', STDOUT_FILENO);
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigterm_handler(int signum)
{
	(void) signum;
	g_exit_status = 127;
	_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
