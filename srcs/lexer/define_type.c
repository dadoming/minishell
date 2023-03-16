/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:47:03 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:15:36 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	define_type(t_shell *mini)
{
	t_list	*tmp;

	tmp = mini->arg_list;
	while (tmp)
	{
		if (string()->_compare_n(tmp->token, "<<", 2) == 0)
		{
			tmp->type = HERE_DOC;
			tmp = tmp->next;
			tmp->type = DELIMITOR;
		}
		else if (string()->_compare_n(tmp->token, ">>", 2) == 0)
		{
			tmp->type = APPEND_OUTPUT;
			tmp = tmp->next;
			tmp->type = OUTFILE_APND;
		}
		else if (string()->_compare_n(tmp->token, "<", 1) == 0)
		{
			tmp->type = RED_INPUT;
			tmp = tmp->next;
			tmp->type = INFILE;
		}
		else if (string()->_compare_n(tmp->token, ">", 1) == 0)
		{
			tmp->type = RED_OUTPUT;
			tmp = tmp->next;
			tmp->type = OUTFILE;
		}
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
