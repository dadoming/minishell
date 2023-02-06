#include "../includes/minishell.h"

/* 
    Checks if there is any input and if there is, add to the 
        history and prepare the values for the parser 
    
    !!! Special Case 2
        For type limitors expand you have to not expand env var.
        For example :
        cat << $HOME

        !!! Special Case 3
        For type IN_FILE and EXIT_FILE you do not have to split env on space,
        Exemple in bash :

        $> Export t="ha  ha"
        $> echo baguette > $t
        $> cat < $t
        baguette

Add rule to check that if char is type limitor to not expand. This should be in the 
expand_dollar function

*/
int evaluate(shell_t *mini)
{
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        lexer(rl_line_buffer, mini);
        if (expander(mini) == 1)
            return (0);
        //if (parser(mini) == TRUE)
          //  return (0);
        if (quotes(mini) == TRUE)
            return (0);
        helper_print(mini->arg_list);
        if (executor(mini) == 1)
            return (1);
    }
    return (0);
}


