/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:44:32 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 00:53:33 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	If env has value then return value else return NULL. 
	Example: get_env(env, "PATH")
*/
char	*get_env(char **env, char *var_name)
{
	int		i;
	int		len;

	len = 0;
	i = 0;
	while (env[i])
	{
		len = string()->_length(var_name);
		if ((string()->_compare_n(env[i], var_name, len) == 0) && \
			(string()->_length_until_c(env[i], '=') == len))
		{
			return (string()->_duplicate(env[i] + len));
		}
		i++;
	}
	return (NULL);
}

char	**set_var(char **env_p, char *var_name, char *var_value)
{
	int	i;

	i = 0;
	while (env_p[i])
	{
		if (string()->_compare_n(env_p[i], var_name, \
			string()->_length(var_name)) == 0 && \
			string()->_length_until_c(env_p[i], '=') == \
			string()->_length(var_name))
		{
			if (var_value)
				substitute_env_var(&env_p[i], var_name, var_value);
			return (env_p);
		}
		i++;
	}
	if (!var_value)
		var_value = "\0";
	env_p = add_to_end_of_env(env_p, var_name, var_value);
	return (env_p);
}
