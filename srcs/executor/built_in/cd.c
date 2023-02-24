#include "../../../includes/minishell.h"

/*
	if no HOME found and no path/args given then print error:
		bash: cd: HOME not set
	if HOME found and no path/args given then change to HOME
	if path/args given then change to path/args
*/

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

char	*my_string_join(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	j = 0;
	i = 0;
	res = malloc(sizeof(char) * (string()->_length(s1) +\
	string()->_length(s2) + 1));
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	**update_env_var(char **env, char *var_name, char *var_value)
{
	char	*new_var;
	int		i;
	int 	var_len = string()->_length(var_name);

	i = 0;
	while (env[i])
	{
		if (string()->_compare_n(env[i], var_name, var_len) == 0 && \
		(string()->_length_until_c(env[i], '=') + 1) == var_len)
		{
			new_var = my_string_join(var_name, var_value);
			free(env[i]);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	return (env);
}

char	*get_curent_dir()
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	return (tmp);
}

void    cd(t_list *lst, char **env)
{
	char	*homedir;
	char	*dir_to_go;
	char	*now_dir;

	homedir = my_getenv("HOME", env);
	now_dir = my_getenv("PWD", env);
	
	if (!lst->next && !homedir)
	{
		 print_normal_error("cd");
		 return;
	}
	env = update_env_var(env, "OLDPWD=", now_dir);
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
	env = update_env_var(env, "OLDPWD=", tmp);
	free(tmp);
	if (chdir(dir_to_go) < 0)
	{
		print_normal_error("cd"); //Err: path;
		return;
	}
	tmp = get_curent_dir();
	env = update_env_var(env, "PWD=", tmp);
	free(tmp);
}
