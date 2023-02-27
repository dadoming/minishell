#include "../../../includes/minishell.h"

extern int g_exit_status;

static int too_many_arguments(char **arg);
int get_total_path(char **path, char *arg, shell_t *mini, char **env, int *print);
static char **set_value(char **env, char *var);
static char **execute_cd(char **env, char *path);
char	*my_getenv(const char *name, char **env);

char **cd(char **arg, char **env, shell_t *mini)
{
	char	*path;
	int print;

	print = 0;
	path = NULL;
	if (too_many_arguments(arg) == 1)
		return (env);
	if (get_total_path(&path, arg[1], mini, env, &print) == 1)
	{
		if (path != NULL)
			free(path);	
		g_exit_status = 1;
		return (env);
	}
	if (!path)
	{
		g_exit_status = 1;
		return (env);
	}
	env = execute_cd(env, path);
	if (print == 1)
		pwd();
	return (env);
}

static char **execute_cd(char **env, char *path)
{
	env = set_value(env, "OLDPWD");
	if (chdir(path) == -1)
	{
		string()->_putstring_fd("minishell: cd: ", 2);
		string()->_putstring_fd(path, 2);
		string()->_putstring_fd(": ", 2);
		string()->_putstring_n_fd(strerror(errno), 2);
		g_exit_status = 1;
		free(path);
		return (env);
	}
	free(path);
	g_exit_status = 0;
	env = set_value(env, "PWD");
	return (env);
}

static int too_many_arguments(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i ++;
	if (i > 2)
	{
		string()->_putstring_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
		return (1);
	}
	return (0);
}

static char **set_value(char **env, char *var)
{
	char *value;
	char *tmp;

	tmp = NULL;
	if (string()->_compare(var, "OLDPWD") == 0)
		tmp = getcwd(NULL, 0);
	if (string()->_compare(var, "PWD") == 0)
		tmp = getcwd(NULL, 0);
	value = string()->_duplicate("=");
	value = string()->_append(&value, tmp);
	env = set_var(env, var, value);
	free(tmp);
	free(value);
	return (env);
}
