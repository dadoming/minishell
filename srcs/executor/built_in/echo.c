/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:57:28 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 22:58:23 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

// 0 for no option, 1 for -n, 2 for invalid option
static int	validate_option(char *option)
{
	if (option[0] == '-' && option[1] == 'n' && option[2] == '\0')
		return (1);
	return (0);
}

static void	perform_echo(int n, char **args, int i)
{
	while (args[i])
	{
		_putstring_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			_putchar_fd(' ', STDOUT_FILENO);
	}
	if (n == 0)
		_putchar_fd('\n', STDOUT_FILENO);
}

//  -n means do not output the trailing newline
int	echo(char **args)
{
	int	n;

	n = 0;
	if (args[1] == NULL)
	{
		_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	if (args[1][0] == '-')
		n = validate_option(args[1]);
	if (n == 1)
		perform_echo(n, args, 2);
	else
		perform_echo(n, args, 1);
	g_exit_status = 0;
	return (0);
}
