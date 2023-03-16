/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:36:26 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 22:36:45 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_normal_error(char *error)
{
	if (error)
	{
		_putstring_fd("minishell: ", 2);
		_putstring_fd(error, 2);
		_putstring_fd(": ", 2);
		_putstring_n_fd(strerror(errno), 2);
	}
}

void	print_error(char *identifier)
{
	_putstring_fd("minishell: export: `", 2);
	_putstring_fd(identifier, 2);
	_putstring_n_fd("': not a valid identifier", 2);
}

void	print_syntax_error(char c)
{
	if (c == '\n')
	{
		_putstring_fd("minishell: syntax error near unexpected token `", 2);
		_putstring_fd("newline", 2);
		_putstring_n_fd("'", 2);
	}
	else if (c)
	{
		_putstring_fd("minishell: syntax error near unexpected token `", 2);
		_putchar_fd(c, 2);
		_putstring_n_fd("'", 2);
	}
}
