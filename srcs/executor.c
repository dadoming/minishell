#include "../includes/minishell.h"

void find_path(char **env, shell_t *mini);
static int is_built_in(shell_t *mini);

int executor(shell_t *mini)
{
	//find_path(mini()->core->env_p); // giving mem_leak
	if (is_built_in(mini) == 1)
		return (1);
	
	
	return (0);
}

static int is_built_in(shell_t *mini)
{
	if(string()->_compare_n(mini->arg_list->token, "echo", 4) == 0 && \
		string()->_length(mini->arg_list->token) == 4)
		echo(mini->arg_list);
	else if(string()->_compare_n(mini->arg_list->token, "cd", 2) == 0 && \
		string()->_length(mini->arg_list->token) == 2)
		cd(mini->arg_list, mini->core->env_p);
	else if(string()->_compare_n(mini->arg_list->token, "pwd", 3) == 0 && \
		string()->_length(mini->arg_list->token) == 3)
		pwd();
	else if(string()->_compare_n(mini->arg_list->token, "export", 6) == 0 && \
		string()->_length(mini->arg_list->token) == 6)
		mini->core->env_p = export(mini->arg_list, mini->core->env_p);
	else if(string()->_compare_n(mini->arg_list->token, "unset", 5) == 0 && \
		string()->_length(mini->arg_list->token) == 5)
		mini->core->env_p = unset(mini->arg_list, mini->core->env_p);
	else if(string()->_compare_n(mini->arg_list->token, "env", 3) == 0 && \
		string()->_length(mini->arg_list->token) == 3)
		env(mini->core->env_p, 2);
	else if(string()->_compare_n(mini->arg_list->token, "exit", 4) == 0 && \
		string()->_length(mini->arg_list->token) == 4)
        return (1);
	return (0);
}

/*
	Returns an array of strings of all the paths present 
		in minishell's environment
*/
void find_path(char **env, shell_t *mini)
{
	while (*env && string()->_compare_n(*env, "PATH=", 5) != 0)
		env++;
	env[0] = env[0] + 5;
	mini->core->execution_path = string()->_split(*env, ':');
}
