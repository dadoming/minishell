#include "../../includes/minishell.h"

void finish_execution(shell_t *mini, t_redirection *red)
{
    int status;

    dup2(red->tmp_in, STDIN_FILENO);
    dup2(red->tmp_out, STDOUT_FILENO);
    close(red->tmp_in);
    close(red->tmp_out);
    if (mini->pid > 0)
    {
        waitpid(mini->pid, &status, 0);
    }
    //if (WIFEXITED(status))
}