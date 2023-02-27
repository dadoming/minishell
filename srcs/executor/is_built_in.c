#include "../../includes/minishell.h"

int is_built_in(t_cmdline *cmdline, shell_t *mini)
{
	if(string()->_same_word(cmdline->cmd, "echo", 4))
	{
		echo(cmdline->arg);
		return (1);
	}
	else if (string()->_same_word(cmdline->cmd, "pwd", 3))
	{
		pwd();
		return (1);
	}
	else if(string()->_same_word(cmdline->cmd, "cd", 2))
	{
		mini->core->env_p = cd(cmdline->arg, mini->core->env_p, mini);
		return (1);
	}
	else if(string()->_same_word(cmdline->cmd, "export", 6))
	{
		mini->core->env_p = export(cmdline->arg, mini->core->env_p);
		return (1);
	}
	else if(string()->_same_word(cmdline->cmd, "unset", 5))
	{
		mini->core->env_p = unset(cmdline->arg, mini->core->env_p);
		return (1);
	}
	else if(string()->_same_word(cmdline->cmd, "env", 3))
	{
		env(mini->core->env_p, 2);
		return (1);
	}
	else if(string()->_same_word(cmdline->cmd, "exit", 4))
	{
		fun_exit(cmdline->arg);
		return (1);
	}
	return (0);
}
