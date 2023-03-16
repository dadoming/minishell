/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:39:18 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 00:39:49 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	no_quote_quote_found(int *outer_quote, \
	char quote, int *location, int *i)
{
	if (*outer_quote == NO_QUOTE && quote == '\'')
	{
		*location = *i;
		*outer_quote = SINGLE_QUOTE;
		(*i)++;
	}
	else if (*outer_quote == NO_QUOTE && quote == '\"')
	{
		*location = *i;
		*outer_quote = DOUBLE_QUOTE;
		(*i)++;
	}
}

void	remove_quote_if_quote_found(int *outer_quote, \
	char *str, int *location, int *i)
{
	if (*outer_quote == DOUBLE_QUOTE && str[*i] == '\"')
	{
		str = remove_quotes(str, '\"', *location);
		*outer_quote = NO_QUOTE;
		*i -= 2;
	}
	else if (*outer_quote == SINGLE_QUOTE && str[*i] == '\'')
	{
		str = remove_quotes(str, '\'', *location);
		*outer_quote = NO_QUOTE;
		*i -= 2;
	}
}
