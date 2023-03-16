/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:46:47 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:46:54 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_quote(int *active_quote, char c)
{
	if (*active_quote == NO_QUOTE)
	{
		if (c == '\'')
			*active_quote = SINGLE_QUOTE;
		else if (c == '\"')
			*active_quote = DOUBLE_QUOTE;
		else
			*active_quote = NO_QUOTE;
	}
	else if (*active_quote == SINGLE_QUOTE)
	{
		if (c == '\'')
			*active_quote = NO_QUOTE;
		else
			*active_quote = SINGLE_QUOTE;
	}
	else if (*active_quote == DOUBLE_QUOTE)
	{
		if (c == '\"')
			*active_quote = NO_QUOTE;
		else
			*active_quote = DOUBLE_QUOTE;
	}
	return (*active_quote);
}
