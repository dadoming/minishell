/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:36:30 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 00:55:36 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

void	separate_token(t_list *aux, int i, char *token2)
{
	char	*token;
	t_list	*new;

	if (!aux->token || !token2 || !*token2)
		return ;
	token = string()->_copy_until(aux->token, i);
	token2 = string()->_duplicate(token2);
	free(aux->token);
	aux->token = token;
	new = list()->_new_node(token2);
	new->next = aux->next;
	aux->next = new;
}

void	fix_expanded_values(t_shell *mini, int quote)
{
	t_list	*aux;
	int		i;

	aux = mini->arg_list;
	i = 0;
	while (aux != NULL)
	{
		while (aux->token[i])
		{
			check_quote(&quote, aux->token[i]);
			if (check()->_is_space(aux->token[i]) == 1 && quote == NO_QUOTE)
			{
				separate_token(aux, i, aux->token + 1 + i);
				break ;
			}
			i++;
		}
		quote = NO_QUOTE;
		aux = aux->next;
		i = 0;
	}
}

char	*treat_quotes(char *str)
{
	int	outer_quote;
	int	location;
	int	i;

	location = 0;
	outer_quote = NO_QUOTE;
	i = 0;
	while (str[i] != '\0')
	{
		no_quote_quote_found(&outer_quote, str[i], &location, &i);
		remove_quote_if_quote_found(&outer_quote, str, &location, &i);
		i++;
	}
	return (str);
}

int	only_one_quote(char *input)
{
	int	i;
	int	outer_quote;
	int	quote_amount;

	outer_quote = NO_QUOTE;
	quote_amount = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (outer_quote == NO_QUOTE && (input[i] == '\'' || input[i] == '\"'))
			assign_outer_quote(input[i], &outer_quote, &quote_amount);
		else if ((outer_quote == DOUBLE_QUOTE && input[i] == '\"') \
			|| (outer_quote == SINGLE_QUOTE && input[i] == '\''))
		{
			outer_quote = NO_QUOTE;
			quote_amount++;
		}
		i++;
	}
	if (quote_amount % 2 != 0)
		return (TRUE);
	return (FALSE);
}
