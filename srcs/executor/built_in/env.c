/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:00:54 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:01:02 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

extern int	g_exit_status;

static void		print_export(char **env);
static char		**load_env_print(char **env);
static void		__print(char **env);
static void		ft_swap(char **a, char **b);

// option1 for export's declare -x, option2 for env command
void	env(char **env_p, int option)
{
	char	*var_name;
	char	*var_value;
	int		i;

	if (option == 1)
	{
		print_export(env_p);
		return ;
	}
	i = 0;
	while (env_p[i] != 0)
	{
		var_name = _copy_until(env_p[i], _length_until_c(env_p[i], '='));
		var_value = _search(env_p[i], '=');
		if (var_value != NULL && option == 2)
			printf("%s%s\n", var_name, var_value);
		if (var_name)
			free(var_name);
		i++;
	}
	g_exit_status = 0;
	return ;
}

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static void	__print(char **env)
{
	int		i;
	char	*var_name;
	char	*var_value;

	if (!env)
		return ;
	i = 0;
	while (env[i] != 0)
	{
		var_name = _copy_until(env[i], _length_until_c(env[i], '='));
		var_value = _search(env[i], '=');
		printf("declare -x %s", var_name);
		if (var_value)
			printf("=\"%s\"\n", var_value + 1);
		else
			printf("\n");
		if (var_name)
			free(var_name);
		i++;
	}
}

static char	**load_env_print(char **env)
{
	char	**env_print;
	int		i;

	if (!env)
		return (NULL);
	env_print = malloc(sizeof(char *) * (string()->_array_length(env) + 1));
	i = 0;
	while (env[i])
	{
		env_print[i] = string()->_duplicate(env[i]);
		i++;
	}
	env_print[string()->_array_length(env)] = 0;
	return (env_print);
}

static void	print_export(char **env)
{
	int		n;
	int		i;
	int		j;
	char	**env_print;

	n = string()->_array_length(env);
	j = 0;
	i = 0;
	env_print = load_env_print(env);
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (string()->_compare(env_print[j], env_print[j + 1]) > 0)
				ft_swap(&env_print[j], &env_print[j + 1]);
			j++;
		}
		i++;
	}
	if (env_print != 0)
		__print(env_print);
	free_array(env_print);
}
