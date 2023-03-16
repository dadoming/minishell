/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:34:12 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 01:38:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

static void	get_full_word(char *buffer, int *i, char separator, t_shell *mini);
static int	check_for_ending_word(char *buffer);
static int	first_char_is_pipe(t_list *arg_list);

/* This function is gonna produce tokens through the input passed
	in through the readline function taking quotes into account*/
int	lexer(char *rl_buffer, t_shell *mini)
{
	int	i;

	i = 0;
	while (rl_buffer[i] != '\0')
	{
		if (rl_buffer[i] == '\'')
			get_full_word(&rl_buffer[i], &i, '\'', mini);
		else if (rl_buffer[i] == '\"')
			get_full_word(&rl_buffer[i], &i, '\"', mini);
		else if (rl_buffer[i] != '\'' && rl_buffer[i] != '\"' && \
				(check()->_is_space(rl_buffer[i]) == FALSE))
		{
			get_full_word(&rl_buffer[i], &i, ' ', mini);
		}
		else
			i++;
	}
	if (first_char_is_pipe(mini->arg_list) == 1)
		return (1);
	if (has_redir(NO_QUOTE, 0, mini->arg_list) == 1)
	{
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	first_char_is_pipe(t_list *arg_list)
{
	if (arg_list->token[0] == '|')
	{
		g_exit_status = 1;
		print_syntax_error('|');
		return (1);
	}
	return (0);
}

static void	get_full_word(char *buffer, int *i, char separator, t_shell *mini)
{
	int	end;

	if (buffer[0] == '\'' || buffer[0] == '\"')
		end = check_for_ending_delimiter(buffer, separator);
	else
		end = check_for_ending_word(buffer) - 1;
	while (_is_space(buffer[end + 1]) == FALSE && buffer[end + 1] != '\0')
	{
		if (buffer[end + 1] == '\'')
			end += check_for_ending_delimiter(&buffer[end + 1], '\'') + 1;
		else if (buffer[end + 1] == '\"')
			end += check_for_ending_delimiter(&buffer[end + 1], '\"') + 1;
		else if (_is_ascii(buffer[end + 1]) == TRUE)
		{
			end += check_for_ending_word(&buffer[end + 1]);
		}
		else
			break ;
	}
	_add_back(&mini->arg_list, _substr(buffer, 0, end + 1));
	(*i) += end + 1;
}

int	check_for_ending_delimiter(char *buffer, char delimiter)
{
	int	i;

	i = 1;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == delimiter)
			return (i);
		i++;
	}
	return (0);
}

static int	check_for_ending_word(char *buffer)
{
	int	i;
	int	aux;

	i = -1;
	aux = 0;
	while (buffer[++i] != '\0')
	{
		if (buffer[i] == '\'')
		{
			aux = check_for_ending_delimiter(&buffer[i], '\'');
			if (aux > 0)
				return (i);
		}
		if (buffer[i] == '\"')
		{
			aux = check_for_ending_delimiter(&buffer[i], '\"');
			if (aux > 0)
				return (i);
		}
		if (_is_space(buffer[i]) == 1)
			return (i);
	}
	if (buffer[i] == '\0')
		return (i);
	return (0);
}
