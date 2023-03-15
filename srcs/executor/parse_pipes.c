#include "../../includes/minishell.h"

/*
 $ echo ola > teste.txt | cat < teste.txt 
ola
cat: -: Bad file descriptor
cat: closing standard input: Bad file descriptor

*/

void parse_pipes(t_cmdline *tree_node, t_redirection *red)
{
    if (tree_node->next != NULL && tree_node->outfile == 0)
    {
        pipe(red->pipe_fd);
        red->fd_out = red->pipe_fd[1];
        red->fd_in = red->pipe_fd[0];
    }
    dup2(red->fd_out, STDOUT_FILENO);
    close(red->fd_out);
    red->fd_out = red->tmp_out;

    //if (red->fd_in == red->fd_out)
    //{
    //    red->fd_in = open("/dev/null", O_RDONLY);
    //    dup2(red->fd_in, STDIN_FILENO);
    //    close(red->fd_in);
    //    //red->fd_in = red->tmp_in;
    //}
}

