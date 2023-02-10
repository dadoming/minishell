#include "../includes/minishell.h"


int evaluate(shell_t *mini)
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        if (lexer(rl_line_buffer, mini) == 1)
            return (0);
        define_type(mini);
        if (expander(mini) == 1)
            return (0);
        if (quotes(mini) == TRUE)
            return (0);
        helper_print(mini->arg_list);
        build_ast(mini->arg_list, mini);
        print_tree(mini->cmdline);
    }
    return (0);
}
