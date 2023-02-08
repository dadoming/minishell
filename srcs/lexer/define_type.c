#include "../../includes/minishell.h"
/*
    If type: HERE_DOC then don't expand word following

    Example: 
    
    $ cat << $HOME
    _______________________________________________________

    If type: OUTFILE and INFILE then expand
    
    Example:

    $ export t="ha ha"
    $ echo baguette > $t
    $ ls
        'ha ha'
    $ cat < $t
        baguette
    _______________________________________________________
    
    If type: word then expand word
    _______________________________________________________
    !!!
    If word starts with "" or '' then set type to WORD
    
    if 
        echo "hello" | wc
            1       1       6
    if 
        echo "hello" '|' wc
            hello | wc
    _______________________________________________________
    
*/

void define_type(shell_t *mini)
{
    t_list *tmp;
    
    tmp = mini->arg_list;
    while (tmp)
    {
        if (string()->_compare_n(tmp->token, "<<", 2) == 0)
        {
            tmp->type = HERE_DOC;
            tmp = tmp->next;
            tmp->type = DELIMITOR;
        }
        else if (string()->_compare_n(tmp->token, ">>", 2) == 0)
        {
            tmp->type = APPEND_OUTPUT;
            tmp = tmp->next;
            tmp->type = OUTFILE_APND;
        }
        else if (string()->_compare_n(tmp->token, "<", 1) == 0)
        {
            tmp->type = RED_INPUT;
            tmp = tmp->next;
            tmp->type = INFILE;
        }
        else if (string()->_compare_n(tmp->token, ">", 1) == 0)
        {
            tmp->type = RED_OUTPUT;
            tmp = tmp->next;
            tmp->type = OUTFILE;
        }
        else if (string()->_compare_n(tmp->token, "|", 1) == 0)
            tmp->type = PIPE;
        else
            tmp->type = WORD;
        tmp = tmp->next;
    }
}