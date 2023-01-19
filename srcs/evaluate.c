#include "../includes/minishell.h"

/* Checks if there is any input and if there is, add to the 
    history and prepare the values for the parser */
int evaluate(void)
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        lexer(rl_line_buffer);
        expander();
        if (quotes() == TRUE)
            return (0);
        helper_print();
    }
    return (0);
}

