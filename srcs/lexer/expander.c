/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:19:32 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:51:24 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void		expand_dollars(char **content, \
	t_shell *mini, int type, int active_quote);
t_list			*remove_node(t_list **arg_list, t_list *node);
static char		*get_variable_name(char *str, int start);

int	expander(t_shell *mini)
{
	t_list	*aux;

	aux = mini->arg_list;
	while (aux != NULL)
	{
		mini->curr_pos = 0;
		expand_dollars(&aux->token, mini, aux->type, NO_QUOTE);
		if (string()->_length(aux->token) == 0)
		{
			aux = remove_node(&mini->arg_list, aux);
			if (aux == NULL)
			{
				if (list()->_size(mini->arg_list) == 0)
					return (1);
				return (0);
			}
			continue ;
		}
		aux = aux->next;
	}
	return (0);
}

t_list	*remove_node(t_list **arg_list, t_list *node)
{
	t_list	*aux;

	aux = *arg_list;
	if (*arg_list == NULL || node == NULL)
		return (NULL);
	if (*arg_list == node)
	{
		*arg_list = node->next;
		free(node->token);
		node->token = NULL;
		free(node);
		node = NULL;
		return (*arg_list);
	}
	else
	{
		while (aux->next != node)
			aux = aux->next;
		aux->next = node->next;
		free(node->token);
		node->token = NULL;
		free(node);
		node = NULL;
	}
	return (aux);
}

int	no_or_double_quote(int quote)
{
	if (quote == NO_QUOTE || quote == DOUBLE_QUOTE)
		return (1);
	return (0);
}

static void	expand_dollars(char **content, t_shell *mini, \
	int type, int active_quote)
{
	char	*str;

	str = *content;
	if ((type == DELIMITOR) || (!*content))
		return ;
	while (str[mini->curr_pos] != '\0')
	{
		check_quote(&active_quote, str[mini->curr_pos]);
		if (str[mini->curr_pos] == '$')
		{
			if ((active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE) && \
				(check()->_is_space(str[mini->curr_pos + 1]) == 0 \
					&& str[mini->curr_pos + 1] != '\0'))
			{
				mini->curr_pos = expand_environment(content, mini, \
					&active_quote, get_variable_name(*content, mini->curr_pos));
				str = *content;
				continue ;
			}
		}
		mini->curr_pos++;
	}
}

static char	*get_variable_name(char *str, int start)
{
	char	variable[131072];
	int		i;
	int		j;

	j = 0;
	i = start + 1;
	if (str[i] == '?')
		return ("$?");
	if (str[i] == '$')
		return ("$$");
	variable[j++] = '$';
	while (str[i] != '\0' && str[i] != '$' && \
		(check()->_is_alnum(str[i]) == 1 || str[i] == '_') \
		&& str[i] != '\'' && str[i] != '\"' && \
		(check()->_is_space(str[i]) == 0))
	{
		variable [j++] = str[i++];
	}
	variable[j] = '\0';
	return (string()->_duplicate(variable));
}
