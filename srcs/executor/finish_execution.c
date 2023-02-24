#include "../../includes/minishell.h"

extern int g_exit_status;

void finish_execution(shell_t *mini, t_redirection *red)
{
    int status;
    int i = 0;

    dup2(red->tmp_in, STDIN_FILENO);
    dup2(red->tmp_out, STDOUT_FILENO);
    close(red->tmp_in);
    close(red->tmp_out);
    while (i < mini->child_num + 1)
    {
        if (mini->pid[i] > 0)
        {
            waitpid(mini->pid[i], &status, 0);
        }
        i++;
    }
    free(mini->pid);
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
}