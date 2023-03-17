/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:40:38 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:00 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

int	_is_alnum(int c)
{
	if (check()->_is_alpha(c) || check()->_is_digit(c))
		return (1);
	else
		return (0);
}

int	_is_alpha(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (2);
	else
		return (0);
}

int	_is_ascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

int	_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	_is_printable(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
