#include "../includes/minishell.h"

/* Checks if there is any input and if there is, add to the 
    history and parse the values for further execution */
int evaluate()
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        lexer(rl_line_buffer);
        printf("#### 1\n");
        helper_print();
        printf("#### 2\n");
        expander();
        if(string()->_compare_n("exit", mini()->arg_list->token, 4) == 0)
            return (1);
    }
    return (0);
}

