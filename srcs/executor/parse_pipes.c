#include "../../includes/minishell.h"

void parse_pipes(t_cmdline *tree_node, t_redirection *red)
{
    if (tree_node->next != NULL && tree_node->outfile != 0)
    {
        pipe(red->pipe_fd);
        red->fd_out = red->pipe_fd[1];
        red->fd_in = red->pipe_fd[0];
    }
    dup2(red->fd_out, STDOUT_FILENO);
    close(red->fd_out);
}
