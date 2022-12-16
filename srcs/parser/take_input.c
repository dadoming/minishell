#include "../../includes/minishell.h"


int check_for_ending_delimiter(char *buffer, char delimiter)
{
    int i = 1;

    while (buffer[i] != '\0')
    {
        if (buffer[i] == delimiter)
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
            iter = check_for_ending_delimiter(&rl_buffer[i], '\'');
            if(iter > 0)
            {
                list()->_add_back(&mini()->arg_list, string()->_substr(rl_buffer, i, iter + 1));
                // inserir type para enum -> single quote
                i += iter + 1;
                (*single_q)++;
            }
        }
        else if(rl_buffer[i] == '\"')
        {
            iter = check_for_ending_delimiter(&rl_buffer[i], '\"');
            if(iter > 0)
            {
                list()->_add_back(&mini()->arg_list, string()->_substr(rl_buffer, i, iter + 1));
                // inserir type para enum -> double quote
                i += iter + 1;
                (*double_q)++;
            }
        }
        // incomplete > It needs to be different from the others, error on: dadoming > minishell$  "hello "yo"
        else if (check()->_is_ascii(rl_buffer[i]) == TRUE && !check()->_is_space(rl_buffer[i])
                && rl_buffer[i] != '\'' && rl_buffer[i] != '\"')
        {
            iter = 1;
            while (rl_buffer[iter] != ' ' && rl_buffer[iter] != '\0' && rl_buffer[i] != '\'' && rl_buffer[i] != '\"')
                iter++;
            if(iter > 0)
            {
                list()->_add_back(&mini()->arg_list, string()->_substr(rl_buffer, i, iter + 1));
                i += iter + 1;
                (*word_amount)++;
            }
        }
        else
        {
            i++;
        }
        iter = 0;
    }
}

void parse(char *rl_buffer)
{
    int single_q = 0;
    int double_q = 0;
    int word_amount = 0;

    check_qs(rl_buffer, &single_q, &double_q, &word_amount);
    print_quote_value(single_q, double_q, word_amount);
    
    
}

