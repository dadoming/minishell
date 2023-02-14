#include "../../includes/minishell.h"

void prepare_command(t_cmdline *aux, char **command, char **path)
{
	*command = get_command(aux->cmd, path);
	if (*command == NULL)
		print_error(aux->cmd, 0);
}

void execute_command(shell_t *mini, char *command, t_cmdline *aux)
{
	mini->pid = fork();
	if (mini->pid == 0)
	{
		execve(command, aux->arg, mini->core->env_p);
	}
	else
	{
		waitpid(mini->pid, NULL, 0);
	}
}

void set_pipes()
{

}

int execute_process(shell_t *mini)
{
	int 		child_num;
	char 		*command;
	char 		**path;
	t_cmdline	*aux;

	aux = mini->cmdline;
	path = find_path(mini->core->env_p);
	command = NULL;
	child_num = 0;
	while (aux)
	{
		set_pipes(child_num, aux);
		prepare_command(aux, &command, path);
		if (command)
		{
			execute_command(mini, command, aux);
			free(command);
		}
		child_num++;
		aux = aux->next;
	}
	free_path(path);
	return (0);
}
