#include "../includes/minishell.h"

void find_path(char **env);

int executor(void)
{
	//find_path(mini()->core->env_p); // giving mem_leak
	if(string()->_compare_n(mini()->arg_list->token, "echo", 4) == 0)
	{
		echo();
	}
	else if(string()->_compare_n(mini()->arg_list->token, "cd", 2) == 0)
	{
		printf("Builtin not done yet\n");
	}
	else if(string()->_compare_n(mini()->arg_list->token, "pwd", 3) == 0)
	{
		printf("Builtin not done yet\n");
	}
	else if(string()->_compare_n(mini()->arg_list->token, "export", 6) == 0)
	{
		printf("Builtin not done yet\n");
	}
	else if(string()->_compare_n(mini()->arg_list->token, "unset", 5) == 0)
	{
		printf("Builtin not done yet\n");
	}
	else if(string()->_compare_n(mini()->arg_list->token, "env", 3) == 0)
	{
		printf("Builtin not done yet\n");
	}
	else if(string()->_compare_n(mini()->arg_list->token, "exit", 4) == 0)
        return (1);
	return (0);
}

/*
	Returns an array of strings of all the paths present 
		in minishell's environment
*/
void find_path(char **env)
{
	while (*env && string()->_compare_n(*env, "PATH=", 5) != 0)
		env++;
	env[0] = env[0] + 5;
	mini()->core->execution_path = string()->_split(*env, ':');
}