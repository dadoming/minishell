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

void print_quote_value(int single_q, int double_q)
{
    printf("\' \' -> %d\n", single_q);
    printf("\" \" -> %d\n", double_q);
}

void check_qs(char *rl_buffer, int *single_q, int *double_q)
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
        if(rl_buffer[i] == '\"')
        {
            iter = check_for_ending_quote(&rl_buffer[i], '\"');
            if(iter > 0)
            {
                i += iter;
                (*double_q)++;
            }
        }
        iter = 0;
        i++;
    }
}

char *trim_buffer(char *buffer)
{
    mini()->trimmed = string()->_trim(buffer, " ");

}


void take_input(char *rl_buffer) // change to return either a list or a **
{
    int single_q = 0;
    int double_q = 0;

    check_qs(rl_buffer, &single_q, &double_q);
    print_quote_value(single_q, double_q);
    // Left to trim string to get desired output
    //trim_buffer();
    mini()->head = load_input(rl_buffer);
    return ;
}
