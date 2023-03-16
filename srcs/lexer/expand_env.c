/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:52:36 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 03:04:11 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char		*remove_unexistent(char *str, int quote, int end, int start);
extern int	g_exit_status;

int	expand_environment(char **content, \
	t_shell *mini, int *active_quote, char *variable)
{
	if (_compare(variable, "$?") == 0)
		return (expand_status(content, variable, active_quote, mini->curr_pos));
	else if (_compare_n(variable, "$$", 2) == 0)
		return (expand_double_dollar(content, active_quote, \
		variable, mini->curr_pos));
    *content = remove_non_existent(mini, *content, NO_QUOTE);
	return (normal_expand(mini, content, active_quote, variable));
}

void	remove_word(char *str, int start, int end)
{
	int	len;

	len = _length(str);
	_mem_move(str + start, str + end, len - end);
	str[len - (end - start)] = '\0';
}

int	next_dollar_position(char *content, int *quote, int curr_pos)
{
	while (content[curr_pos] != '\0')
	{
		if (content[curr_pos] == '\'' || content[curr_pos] == '\"')
			check_quote(quote, content[curr_pos]);
		if (content[curr_pos] == '$' && \
			(*quote == NO_QUOTE || *quote == DOUBLE_QUOTE))
		{
			return (curr_pos);
		}
		curr_pos++;
	}
	return (curr_pos);
}
