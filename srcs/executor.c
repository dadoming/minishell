#include "../includes/minishell.h"

static int is_built_in(t_cmdline *cmdline, shell_t *mini, int child_num);

int set_pipes(shell_t *mini)
{
	int i = 0;

	mini->num_of_pipes = 2 * ((mini->num_of_cmds) - 1);
	printf("Num of pipes: %d\n", mini->num_of_pipes);
	mini->fd = (int *)malloc(sizeof(int) * mini->num_of_pipes);
	if (!mini->fd)
	{
		perror("malloc");
		return (1);
	}
	while (i < mini->num_of_pipes - 1)
	{
		if (pipe(mini->fd) < 0)
		{
			perror("pipe");
			return (2);
		}
		i++;
	}
	return (0);
}

int executor(shell_t *mini)
{
	int built_in;
	int child_num;
	t_cmdline *aux;

	built_in = 0;
	aux = mini->cmdline;
	child_num = 0;
	if (mini->num_of_cmds > 1)
		set_pipes(mini);
	while (aux)
	{
		built_in = is_built_in(aux, mini, child_num);
		if (built_in >= 1)
		{
			if (built_in == 1)
				return (1);
			built_in = 0;
			child_num++;
		}
		else
		{
			execute_process(mini, aux, child_num);
			child_num++;
		}
		aux = aux->next;
	}
	return (0);
}

static void fds(shell_t *mini, int child_num)
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
			close(mini->fd[2 * child_num - 2]);
			close(mini->fd[2 * child_num + 1]);
		}
	}
}

static int is_built_in(t_cmdline *cmdline, shell_t *mini, int child_num)
{	
	if(string()->_same_word(cmdline->cmd, "echo", 4))
	{
		fds(mini, child_num);
		echo(cmdline->arg);
		return (2);
	}
	else if(string()->_same_word(mini->arg_list->token, "cd", 2))
	{
		cd(mini->arg_list, mini->core->env_p);
		return (2);
	}
	else if(string()->_same_word(cmdline->cmd, "pwd", 3))
	{
		pwd();
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
