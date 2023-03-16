/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:03:24 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/16 01:09:01 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

static char		**fill_new_value(char **new_env, int i, \
	char *var_name, char *var_value);
char			**export_to_env(char **env_p, char **arg, \
	char *var_name, char *var_value);

char	**export(char **arg, char **env_p)
{
	char	*var_name;
	char	*var_value;

	if (!arg[1])
	{
		env(env_p, 1);
		return (env_p);
	}
	var_name = NULL;
	var_value = NULL;
	env_p = export_to_env(env_p, arg, var_name, var_value);
	g_exit_status = 0;
	return (env_p);
}

char	**export_to_env(char **env_p, char **arg, \
	char *var_name, char *var_value)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		var_name = NULL;
		var_value = NULL;
		if (arg[i])
		{
			if (check()->_is_alpha(arg[i][0]) == 0 && arg[i][0] != '_')
			{
				print_error(arg[i]);
				g_exit_status = 1;
				return (env_p);
			}
			var_name = string()->_copy_until(arg[i], \
				string()->_length_until_c(arg[i], '='));
			var_value = string()->_search(arg[i], '=');
		}
		if (var_name)
			env_p = set_var(env_p, var_name, var_value);
		free(var_name);
		i++;
	}
	return (env_p);
}

void	substitute_env_var(char **env_p, char *var_name, char *var_value)
{
	int		i;
	int		j;
	char	*new_env;

	i = 0;
	j = 0;
	new_env = malloc(sizeof(char) * \
		(_length(var_name) + _length(var_value) + 2));
	while (var_name[j])
	{
		new_env[j] = var_name[j];
		j++;
	}
	while (var_value[i])
	{
		new_env[j] = var_value[i];
		j++;
		i++;
	}
	new_env[j] = '\0';
	free(*env_p);
	*env_p = new_env;
}

static char	**fill_new_value(char **new_env, int i, \
	char *var_name, char *var_value)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	new_env[i] = malloc(sizeof(char) * \
		(string()->_length(var_name) + string()->_length(var_value) + 2));
	while (var_name[j])
	{
		new_env[i][j] = var_name[j];
		j++;
	}
	while (var_value[k] != '\0')
	{
		new_env[i][j] = var_value[k];
		j++;
		k++;
	}
	new_env[i][j] = '\0';
	new_env[i + 1] = NULL;
	return (new_env);
}

char	**add_to_end_of_env(char **env_p, char *var_name, char *var_value)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (string()->_array_length(env_p) + 2));
	while (env_p[i])
	{
		new_env[i] = string()->_duplicate(env_p[i]);
		free(env_p[i]);
		i++;
	}
	new_env = fill_new_value(new_env, i, var_name, var_value);
	free(env_p);
	return (new_env);
}
