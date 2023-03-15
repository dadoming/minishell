#include "../includes/minishell.h"

// Just to not give a valgrind error -.-
void init_(shell_t *mini, t_redirection *red)
{
	int i = 0;

	mini->pid = malloc(sizeof(int) * (mini->child_num + 1));
	mini->clear_pid = 1;
	while (i < mini->child_num + 1)
	{
		mini->pid[i] = 0;
		i++;
	}
    red->tmp_in = dup(STDIN_FILENO);
	red->tmp_out = dup(STDOUT_FILENO);
	red->fd_in = dup(red->tmp_in);
    red->fd_out = dup(red->tmp_out);
}

int executor(shell_t *mini, t_cmdline *aux)
{
	t_redirection red;
	int i = 0;

	init_(mini, &red);
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
		execute_command(mini, aux, i);
		aux = aux->next;
		i++;
        //reset_fds(&red);
    }
	reset_fds(&red);
	return (0);
}
