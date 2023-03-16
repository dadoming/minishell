/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 22:45:20 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 22:45:57 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clear_core(t_shell **mini);

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_program(t_shell **mini)
{
	clear_looped_values(mini);
	clear_core(mini);
	rl_erase_empty_line = 1;
	rl_clear_history();
	free(*mini);
	return ;
}

static void	clear_core(t_shell **mini)
{
	if ((*mini)->core->home != NULL)
		free((*mini)->core->home);
	free_array((*mini)->core->env_p);
	free((*mini)->core);
}
