#include "../includes/minishell.h"

/* Checks if there is any input and if there is, add to the 
    history and prepare the values for the parser */
int evaluate(shell_t *mini)
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        lexer(rl_line_buffer, mini);
        expander(mini);
        //if (parser(mini) == TRUE)
          //  return (0);
        if (quotes(mini) == TRUE)
            return (0);
        //helper_print(mini->arg_list);
        if (executor(mini) == 1)
            return (1);
    }
    return (0);
}


