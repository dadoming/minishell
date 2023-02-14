#include "../../includes/minishell.h"

char	*get_command(char *command, char **path)
{
	char	*tmp;
	char	*cmd;
	int 	i = 0;

	if (path == NULL)
	{
		return (NULL);
	}
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

char **find_path(char **env)
{
	char **path;
	int i;

	i = 0;
	path = NULL;

	while (env[i])
	{
		if (string()->_compare_n(env[i], "PATH=", 5) == 0)
		{
			path = string()->_split(env[i] + 5, ':');
			break;
		}
		i++;
	}
	return (path);
}

void free_path(char **path)
{
	if (path != NULL)
	{
		int i = 0;
		while (path[i] != NULL)
		{
			free(path[i]);
			i++;
		}
		free(path);
	}
}
