#include "../includes/minishell.h"

extern int g_exit_status;

int evaluate(shell_t *mini)
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        if (lexer(rl_line_buffer, mini) == 1)
            return (1);
        define_type(mini);
        if (expander(mini) == 1)
            return (1);
        if (quotes(mini) == TRUE)
            return (1);
        if (list()->_size(mini->arg_list) > 0)
        {
            if (build_ast(mini->arg_list, mini) == 1)
            {
                g_exit_status = 1;
                string()->_putstring_n_fd("The first word needs to be a command", 2);
                return (1);
            }
        }
        return (0);
    }
    g_exit_status = 0;
    return (1);
}
