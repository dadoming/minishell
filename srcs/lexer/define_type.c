/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:47:03 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 12:58:35 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*assign(t_list *tmp, int this, int next)
{
	tmp->type = this;
	tmp = tmp->next;
	tmp->type = next;
	return (tmp);
}

void	define_type(t_shell *mini)
{
	t_list	*tmp;

	tmp = mini->arg_list;
	while (tmp)
	{
		if (string()->_compare_n(tmp->token, "<<", 2) == 0)
			tmp = assign(tmp, HERE_DOC, DELIMITOR);
		else if (string()->_compare_n(tmp->token, ">>", 2) == 0)
			tmp = assign(tmp, APPEND_OUTPUT, OUTFILE_APND);
		else if (string()->_compare_n(tmp->token, "<", 1) == 0)
			tmp = assign(tmp, RED_INPUT, INFILE);
		else if (string()->_compare_n(tmp->token, ">", 1) == 0)
			tmp = assign(tmp, RED_OUTPUT, OUTFILE);
		else if (string()->_compare_n(tmp->token, "|", 1) == 0)
		{
			tmp->type = PIPE;
			mini->child_num++;
		}
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}
