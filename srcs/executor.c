#include "../includes/minishell.h"

// Just to not give a valgrind error -.-
void init_pid(shell_t *mini)
{
	int i = 0;

	mini->pid = malloc(sizeof(int) * (mini->child_num + 1));
	mini->clear_pid = 1;
	while (i < mini->child_num + 1)
	{
		mini->pid[i] = 0;
		i++;
	}
}

int executor(shell_t *mini, t_cmdline *aux)
{
	t_redirection red;
	int i = 0;

	red.tmp_in = dup(STDIN_FILENO);
	red.tmp_out = dup(STDOUT_FILENO);
	red.fd_in = dup(red.tmp_in);
	init_pid(mini);
	while (aux != NULL)
	{
		parse_outfile(aux, &red);
		if (parse_infile(mini, aux, &red) == -1)
			return (0);
		if (red.fd_out == -1)
			break;
		parse_pipes(aux, &red);
		if (is_built_in(aux, mini) == 1)
		{
			aux = aux->next;
			continue;
		}
		execute_command(mini, aux, &red, i);
		aux = aux->next;
		i++;
	}
	finish_execution(&red);
	return (0);
}
