/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 23:11:44 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/15 23:12:17 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_command(char *command, char **path)
{
	char	*tmp;
	char	*cmd;
	int		i;

	i = 0;
	if (path == NULL)
		return (NULL);
	if (access(command, F_OK) == 0 && access(command, X_OK) == 0)
		return (string()->_duplicate(command));
	while (path[i])
	{
		tmp = string()->_join(path[i], "/");
		cmd = string()->_join(tmp, command);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

char	**find_path(char **env)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (string()->_compare_n(env[i], "PATH=", 5) == 0)
		{
			path = string()->_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (path);
}
