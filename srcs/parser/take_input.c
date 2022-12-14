#include "../../includes/minishell.h"

/*
c1r18s8% echo "   s'  "
   s'  

c1r18s8% echo "   s' $PWD  "
   s' /nfs/homes/dadoming/minishell  

c1r18s8% echo '"   s $PWD  "' 
"   s $PWD  "

*/



int check_for_ending_quote(char *rl_buffer, char delimiter)
{
    int i = 1;

    while (rl_buffer[i] != '\0')
    {
        if (rl_buffer[i] == delimiter)
            return (i);
        i++;
    }
    return (FALSE);
}

void check_qs(char *rl_buffer, int *single_q, int *double_q, int *word_amount)
{
    int i = 0;
    int iter = 0;

    while (rl_buffer[i] != '\0')
    {
        if(rl_buffer[i] == '\'')
        {
            iter = check_for_ending_quote(&rl_buffer[i], '\'');
            if(iter > 0)
            {
                i += iter;
                (*single_q)++;
            }
        }
        else if(rl_buffer[i] == '\"')
        {
            iter = check_for_ending_quote(&rl_buffer[i], '\"');
            if(iter > 0)
            {
                i += iter;
                (*double_q)++;
            }
        }
        // incomplete
        else if ((check()->_is_ascii(rl_buffer[i]) == TRUE && !check()->_is_space(rl_buffer[i])
                && (check()->_is_space(rl_buffer[i + 1]) == TRUE || rl_buffer[i + 1] == '\0')))
            (*word_amount)++;
        iter = 0;
        i++;
    }
}

t_list *take_input(char *rl_buffer)
{
    t_list *arguments;
    int single_q = 0;
    int double_q = 0;
    int word_amount = 0;

    arguments = NULL;
    check_qs(rl_buffer, &single_q, &double_q, &word_amount);
    print_quote_value(single_q, double_q, word_amount);
    
    char **trimmed = malloc(sizeof(char *) * (single_q + double_q + word_amount) + 1);
    trimmed[single_q + double_q + word_amount] = 0;
    trim_string(rl_buffer, &trimmed);
    
    int i = 0;
    while (trimmed[i] != 0)
    {
        printf("%s\n", trimmed[i]);
        i++;
    }
    
    arguments = load_input(trimmed, arguments);
    return (arguments);
}

