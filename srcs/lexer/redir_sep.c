/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_sep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:38:24 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 00:39:07 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_redir(char *str, int i)
{
	if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (1);
	return (0);
}

int	next_node_is_redirect(char *next_node_str)
{
	if (next_node_str == NULL)
	{
		print_syntax_error('\n');
		return (1);
	}
	if (is_redir(next_node_str, 0) == 1)
	{
		print_syntax_error(next_node_str[0]);
		return (1);
	}
	return (0);
}

void	redirect_at_beggining(char *str, int i, t_list **lst, t_list *aux)
{
	char	*str_left;
	t_list	*new;

	while (is_redir(str, i) == 1)
			i++;
	str_left = string()->_duplicate(&str[i]);
	(*lst)->token[i] = '\0';
	new = list()->_new_node(str_left);
	(*lst)->next = new;
	if (aux != NULL)
		(*lst)->next->next = aux;
}

void	redirect_at_middle_or_end(char *str, int i, t_list **lst, t_list *aux)
{
	char	*str_left;
	t_list	*new;

	str_left = string()->_duplicate(&str[i]);
	(*lst)->token[i] = '\0';
	new = list()->_new_node(str_left);
	(*lst)->next = new;
	if (aux != NULL)
		(*lst)->next->next = aux;
}
