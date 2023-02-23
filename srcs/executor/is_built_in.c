#include "../../includes/minishell.h"

int is_built_in(t_cmdline *cmdline, shell_t *mini)
{
	if(string()->_same_word(mini->arg_list->token, "cd", 2))
	{
		cd(mini->arg_list, mini->core->env_p);
		return (2);
	}
	else if(string()->_same_word(cmdline->cmd, "export", 6))
	{
		mini->core->env_p = export(cmdline->arg, mini->core->env_p);
		return (2);
	}
	else if(string()->_same_word(cmdline->cmd, "unset", 5))
	{
		mini->core->env_p = unset(cmdline->arg, mini->core->env_p);
		return (2);
	}
	else if(string()->_same_word(cmdline->cmd, "env", 3))
	{
		env(mini->core->env_p, 2);
		return (2);
	}
	if(string()->_same_word(cmdline->cmd, "exit", 4))
		return (1);
	return (0);
}
