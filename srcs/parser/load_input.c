#include "../../includes/minishell.h"


/*

c1r18s8% echo hello' to all'
hello to all
c1r18s8% echo hello ' to all'
hello  to all
c1r18s8% echo hello' to all' 
hello to all
c1r18s8% echo hello ' to all'
hello  to all
c1r18s8% echo hello        ' to all' of "you"
hello  to all of you

i can tokenize anyway. it will execute echo on the entire input line.
*/

/* 
    Get token list from input.
    Use substr to send input to the mini()->head->token
    It will retrieve each token until:
    -> space found;
    -> single quote found;
    -> double quote found;

*/

int delimiter_found(char c)
{
    if(c == '\''|| c == '\"' || c == ' ')
        return (TRUE);
    return (FALSE);
}

t_list *load_input(char *buffer, t_list *arguments)
{
    int i = 0;
    int start = 0;
 
    while (buffer[i] != '\0')
    {
        if(delimiter_found(buffer[i]) == TRUE || !buffer[i + 1])
        {
            list()->_add_back(&arguments, string()->_substr(buffer, start, i - start + 1));
            start = i + 1;
        }
        i++;
    }
    return (arguments);
}
