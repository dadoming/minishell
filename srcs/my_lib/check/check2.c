/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:40:48 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:09 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

int	_is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' \
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	_is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
}

//  . $ * + ? | "\\" ^ [ { (
int	_is_meta_char(char c)
{
	if (c == 46 || c == 36 || c == 42 || c == 43 \
		|| c == 63 || c == 124 || c == 92 || c == 94 \
		|| c == 91 || c == 123 || c == 40)
		return (1);
	return (0);
}
