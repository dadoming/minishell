#include "../../../includes/minishell.h"

extern int g_exit_status;

static int	set_path(char **path, char *env_var, char **env);
static int set_dash(char **path, char **env, char *arg, int *print);
static int set_tilde(char **path, char *arg, shell_t *mini);

int get_total_path(char **path, char *arg, shell_t *mini, char **env, int *print)
{
	if (!arg)
	{
		if (set_path(path, "HOME", env) == 1)
			return (1);
	}
	else if (arg[0] == '-')
	{
		if (set_dash(path, env, arg, print) == 1)
			return (1);
	}
	else if (arg[0] == '~')
	{
		if (set_tilde(path, arg, mini) == 1)
			return (1);
	}
	else
		*path = string()->_duplicate(arg);
	return (0);
}

static int set_tilde(char **path, char *arg, shell_t *mini)
{
	*path = string()->_duplicate(mini->core->home);
	if (!*path)
	{
		string()->_putstring_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	if (arg[1] == '/')
		*path = string()->_append(path, &arg[1]);
	return (0);
}

static int set_dash(char **path, char **env, char *arg, int *print)
{
	if (arg[0] == '-' && arg[1] == '\0')
	{
		if (set_path(path, "OLDPWD", env) == 1)
			return (1);
		*print = 1;
	}
	if (arg[1] == '-' && arg[2] == '\0')
	{
		if (set_path(path, "HOME", env) == 1)
			return (1);
	}
	if ((arg[1] != '-' && arg[1] != '\0') || string()->_length(arg) > 2)
	{
		string()->_putstring_fd("minishell: cd: ", 2);
		string()->_putstring_fd(arg, 2);
		string()->_putstring_fd(": invalid option\n", 2);
		return (1);
	}
	return (0);
}

static int	set_path(char **path, char *env_var, char **env)
{
	char	*tmp;

	tmp = my_getenv(env_var, env);
	if (tmp)
		*path = string()->_duplicate(tmp);
	else
	{
		string()->_putstring_fd("minishell: cd: ", 2);
		string()->_putstring_fd(env_var, 2);
		string()->_putstring_fd(": not set\n", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

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