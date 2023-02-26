#include "../../../includes/minishell.h"

char	*my_getenv(const char *name, char **env)
{
	int	len;
	int	i;

	i = 0;
	len = string()->_length(name);
	while (env[i] != NULL)
	{
		if (string()->_compare_n(env[i], name, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

int	set_env_var(char **my_env, const char *var_name, const char *new_value)
{
	int	var_index;
	int	var_name_len;
	int	new_value_len;
	int i;
	char	*new_env_var;
	char	*p;
	
	var_index = -1;
	var_name_len = string()->_length(var_name);
	new_value_len = string()->_length(new_value);
	i = 0;
	
	while (my_env[i] != NULL)
	{
		if (string()->_compare_n(my_env[i], var_name, string()->_length(var_name)) == 0 && my_env[i][strlen(var_name)] == '=')
		{
			var_index = i;
			break ;
		}
		i++;
	}
	if (var_index == -1)
		return (-1);
	new_env_var = malloc(var_name_len + new_value_len + 2);
	if (new_env_var == NULL)
		return (-1);
	p = new_env_var;
	i = 0;
	while (i < new_value_len)
	{
		*p++ = new_value[i];
		i++;
	}
	*p = '\0';
	free(my_env[var_index]);
	my_env[var_index] = new_env_var;
	return (0);
}


char	*get_curent_dir()
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	return (tmp);
}

void    cd(t_list *lst, char **env)
{
	char 	*homedir;
	char 	*dir_to_go;
	char 	*now_dir;

	homedir = my_getenv("HOME", env);
	now_dir = my_getenv("PWD", env);

	if (!lst->next && !homedir)
	{
		print_normal_error("cd");
		return ;
	}
	set_env_var(env, "OLDPWD", now_dir);
	if (!lst->next && homedir)
		dir_to_go = homedir;
	else if (lst->next->token[0] == '/')
		dir_to_go = lst->next->token;
	else if (string()->_compare(lst->next->token, "..") == 0)
		dir_to_go = "..";
	else if(string()->_compare(lst->next->token, ".") == 0)
		dir_to_go = now_dir;
	else
		dir_to_go = lst->next->token;
	char *tmp;
	tmp = get_curent_dir();
	set_env_var(env, "OLDPDW", tmp);
	free(tmp);
	if (chdir(dir_to_go) < 0)
	{
		print_normal_error("cd"); //Err: path;
		return;
	}
	tmp = get_curent_dir();
	set_env_var(env, "PWD", tmp);
	free(tmp);
}

