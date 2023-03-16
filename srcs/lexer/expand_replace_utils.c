/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:11:15 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:43:27 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	norm_iter(char **if_this_has, int *iter);

int	calculate_size(char **if_this_has, char *this, \
	char *str_to_replace, int active_quote)
{
	int	total_return_size;
	int	size;

	size = _length(this);
	total_return_size = 0;
	while (**if_this_has != '\0')
	{
		if (**if_this_has == '\'' || **if_this_has == '\"')
		{
            check_quote(&active_quote, **if_this_has);
            norm_iter(if_this_has, &total_return_size);
            continue ;
		}
		if (_compare_n(*if_this_has, this, size) == 0 && str_to_replace && active_quote != SINGLE_QUOTE)
		{
			total_return_size += string()->_length(str_to_replace);
			(*if_this_has) += size;
		}
		else
            norm_iter(if_this_has, &total_return_size);
	}
	return (total_return_size);
}

void	norm_iter(char **if_this_has, int *iter)
{
    (*iter)++;
    (*if_this_has)++;
}

