#include "../includes/minishell.h"

static int is_built_in(shell_t *mini);

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
