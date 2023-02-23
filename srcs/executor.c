#include "../includes/minishell.h"

/*

davz@davz-rog:~$ echo "lol" > outfile this
davz@davz-rog:~$ ls
Desktop    Downloads  git_repos  Music    Pictures  snap       Videos
Documents  etc        GPUCache   outfile  Public    Templates
davz@davz-rog:~$ cat outfile 
lol this
davz@davz-rog:~$ 

*/
/*
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
*/


int executor(shell_t *mini, t_cmdline *aux)
{
	t_redirection red;

	red.tmp_in = dup(STDIN_FILENO);
	red.tmp_out = dup(STDOUT_FILENO);
	red.fd_in = dup(red.tmp_in);
	while (aux != NULL)
	{
		parse_outfile(aux, &red);
		if (parse_infile(mini, aux, &red) == -1)
			return (0);
		if (red.fd_out == -1)
			break;
		parse_pipes(aux, &red);
		if (is_built_in(aux, mini) == 2)
		{
			aux = aux->next;
			continue;
		}
		execute_command(mini, aux);
		aux = aux->next;
	}
	finish_execution(mini, &red);
	return (0);
}


