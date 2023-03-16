/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:36:51 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:50:35 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	assign_outer_quote(char c, int *outer_quote, int *quote_amount)
{
	if (c == '\'')
		*outer_quote = SINGLE_QUOTE;
	if (c == '\"')
		*outer_quote = DOUBLE_QUOTE;
	(*quote_amount)++;
}

char	*remove_quotes(char *str, char c, int i)
{
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			_mem_move(&str[i], &str[i + 1], string()->_length(str) - i);
			if (i > 0)
				i--;
			while (str[i] != c && str[i] != '\0')
				i++;
			_mem_move(&str[i], &str[i + 1], string()->_length(str) - i);
			break ;
		}
		i++;
	}
	return (str);
}

int	quotes(t_shell *mini)
{
	t_list	*aux;

	fix_expanded_values(mini, NO_QUOTE);
	aux = mini->arg_list;
	while (aux != NULL)
	{
		if (only_one_quote(aux->token) == TRUE)
		{
			_putstring_n_fd("Unclosed quotes!", 2);
			g_exit_status = 1;
			return (TRUE);
		}
		aux->token = treat_quotes(aux->token);
		aux = aux->next;
	}
	return (0);
}
