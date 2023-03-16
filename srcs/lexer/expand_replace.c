/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:52:54 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 02:44:23 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char		*copy_env_value(char *str_to_replace, char *ret, int *i);
static char		*copy_value(char *ret, char **if_this_has, int *i);
void			norm_iter(char **if_this_has, int *iter);

char	*return_array_norm(char **if_this_has, \
	char *this, char *str_to_replace, char *free_mem)
{
	char	*ret;

	ret = malloc (sizeof(char) * (calculate_size(if_this_has, this, \
		str_to_replace, NO_QUOTE) + 1));
	*if_this_has = free_mem;
	return (ret);
}

static char	*replace_norm(char **if_this_has, \
	char *this, char *str_to_replace, char *ret)
{
	int		size;
	int		i;
	int		active_quote;

	active_quote = NO_QUOTE;
	i = 0;
	size = string()->_length(this);
	while (**if_this_has != '\0')
	{
		if (**if_this_has == '\'' || **if_this_has == '\"')
		{
            check_quote(&active_quote, **if_this_has);
			ret[i++] = *(*if_this_has)++;
            continue ;
		}
		if (string()->_compare_n(*if_this_has, this, size) == 0 && active_quote != SINGLE_QUOTE)
		{
			ret = copy_env_value(str_to_replace, ret, &i);
			*if_this_has += size;
		}
		else
			ret = copy_value(ret, if_this_has, &i);
	}
	ret[i] = '\0';
	return (ret);
}

char	*replace(char **if_this_has, char *this, \
	char *str_to_replace)
{
	char	*ret;
	char	*free_mem;

	free_mem = *if_this_has;
	ret = return_array_norm(if_this_has, this, str_to_replace, free_mem);
	ret = replace_norm(if_this_has, this, str_to_replace, ret);
	free(free_mem);
	return (ret);
}

static char	*copy_env_value(char *str_to_replace, char *ret, int *i)
{
	int	j;

	j = 0;
	while (str_to_replace[j] != '\0')
	{
		ret[(*i)++] = str_to_replace[j++];
	}
	return (ret);
}

static char	*copy_value(char *ret, char **if_this_has, int *i)
{
	ret[*i] = **if_this_has;
	(*if_this_has)++;
	(*i)++;
	return (ret);
}
