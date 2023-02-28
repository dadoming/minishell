#include "../../includes/minishell.h"

extern int g_exit_status;

void reset_fds(t_redirection *red)
{
    dup2(red->tmp_in, STDIN_FILENO);
    dup2(red->tmp_out, STDOUT_FILENO);
    close(red->tmp_in);
    close(red->tmp_out);
}
