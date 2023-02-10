#include "../includes/minishell.h"

char  **find_path(char **env);
static int is_built_in(shell_t *mini);
char	*get_command(char *command, char **path);
char	*ft_strjoin(char const *s1, char const *s2);

int execute_process(shell_t *mini)
{
	int 		child;
	t_cmdline	*aux;
	int pid = 0;

	// Get number of child processes
	child = 0;

	aux = mini->cmdline;

	while (aux)
	{
		child++;
		aux = aux->next;
	}

	aux = mini->cmdline;

	printf("There are %d child processes to be executed\n", child);

	// Get full path 
	char **path = find_path(mini->core->env_p);

	// Get command and free path cause we don't need it anymore
	char *command = get_command(aux->cmd, path);
	if (command == NULL)
	{
		print_error(aux->cmd, 0);
	}

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
	
	
	// Execute command
	pid = fork();
	if (pid == 0)
	{
		execve(command, aux->arg, mini->core->env_p);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}


	return (0);
}


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
		tmp = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	j = 0;
	i = -1;
	str = malloc(sizeof(char) * (string()->_length(s1) + string()->_length(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}


/*
	Returns an array of strings of all the paths present 
		in minishell's environment
*/
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


int executor(shell_t *mini)
{
	int built_in;
	
	built_in = is_built_in(mini);
	if (built_in == 1)
		return (1);
	else if (built_in == 0)
		return (0);
	
	else
	{
		execute_process(mini);
		return (0);
		// waitpid();
	}
	
	return (0);
}

static int is_built_in(shell_t *mini)
{
	if(string()->_same_word(mini->arg_list->token, "echo", 4))
	{
		echo(mini->arg_list);
		return (0);
	}
	else if(string()->_same_word(mini->arg_list->token, "cd", 2))
	{
		cd(mini->arg_list, mini->core->env_p);
		return (0);
	}
	else if(string()->_same_word(mini->arg_list->token, "pwd", 3))
	{
		pwd();
		return (0);
	}
	else if(string()->_same_word(mini->arg_list->token, "export", 6))
	{
		mini->core->env_p = export(mini->arg_list, mini->core->env_p);
		return (0);
	}
	else if(string()->_same_word(mini->arg_list->token, "unset", 5))
	{
		mini->core->env_p = unset(mini->arg_list, mini->core->env_p);
		return (0);
	}
		
	else if(string()->_same_word(mini->arg_list->token, "env", 3))
	{
		env(mini->core->env_p, 2);
		return (0);
	}
	else if(string()->_same_word(mini->arg_list->token, "exit", 4))
    {
		return (1);
	}
	return (2);
}

