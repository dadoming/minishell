#include "../../includes/minishell.h"

void prepare_command(t_cmdline *aux, char **command, char **path)
{
	*command = get_command(aux->cmd, path);
	if (*command == NULL)
		print_error(aux->cmd, 0);
}
/*

void execute_command(shell_t *mini, char *command, char **arg, int child_num)
{
	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (mini->num_of_cmds > 1)
		{
			if (child_num == 0)
			{
				dup2(mini->fd[STDOUT_FILENO], STDOUT_FILENO);
				close(mini->fd[STDIN_FILENO]);
				close(mini->fd[STDOUT_FILENO]);
			}
			else if (child_num == (mini->num_of_cmds - 1))
			{
				dup2(mini->fd[(2 * child_num) - 2], STDIN_FILENO);
				close(mini->fd[(2 * child_num) - 1]);
				close(mini->fd[(2 * child_num) - 2]);
			}
			else
			{
				dup2(mini->fd[2 * child_num - 2], STDIN_FILENO);
				dup2(mini->fd[2 * child_num + 1], STDOUT_FILENO);
			}
		}
		execve(command, arg, mini->core->env_p);
	}
	else if (mini->pid == -1)
	{
		perror("fork");
		exit(1);
	}
}

int execute_process(shell_t *mini, t_cmdline *cmdline, int child_num)
{
	char 		*command;
	char 		**path;

	path = find_path(mini->core->env_p);
	command = NULL;
	prepare_command(cmdline, &command, path);
	if (command)
	{
		execute_command(mini, command, cmdline->arg, child_num);
		free(command);
		if (mini->num_of_cmds > 1)
		{
			// Close appropriate file descriptors
			if (child_num > 0) {
				close(mini->fd[(child_num-1)*2]); // Close write end of previous pipe
			}
			if (child_num < mini->num_of_cmds-1) {
				close(mini->fd[child_num*2+1]); // Close read end of current pipe
			}
		}
	}
	waitpid(-1, NULL, 0);
	free_path(path);
	return (0);
}
*/ 
