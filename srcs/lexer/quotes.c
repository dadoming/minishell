#include "../../includes/minishell.h"

static int only_one_quote(char *input);

int quotes(void)
{
    t_list *aux;

    aux = mini()->arg_list;
    while (aux != NULL)
    {
        if (only_one_quote(aux->token) == TRUE)
        {
            printf("Unclosed quotes\n");
            return (TRUE);
        }
        //aux->token = 
        aux = aux->next;
    }
    
    return (FALSE);
    // remove_double_quotes(&content, 0, 0);
}

// Removes all double quotes in the sentence. Needs to be tweaked to only remove the neccessary ones
void remove_double_quotes(char **aux, int i, int end)
{
    char *content;

    content = *aux;
    while (content[i] != '\0')
    {
        if (content[i] == '\"')
        {
            string()->_mem_move(&content[i], &content[i + 1], string()->_length(content) - i);
            i--;
            end = string()->_length(content);
            while (content[end] != '\"')
            {
                end--;
                if (content[end] == '\"')
                {
                    string()->_mem_move(&content[end], &content[end + 1], string()->_length(content) - end);
                    break;
                }
                if (end == 0)
                    break;
            }
        }
        i++;
    }
}

static int only_one_quote(char *input)
{
    int i;
    int outer_quote;
    int quote_amount;

    outer_quote = NO_QUOTE;
    quote_amount = 0;
    i = 0;
    while (input[i] != '\0')
    {
        if (outer_quote == NO_QUOTE && (input[i] == '\'' || input[i] == '\"'))
        {
            if (input[i] == '\'')
                outer_quote = SINGLE_QUOTE;
            if (input[i] == '\"')
                outer_quote = DOUBLE_QUOTE; 
            quote_amount++;
            i++;
        }
        if (outer_quote == DOUBLE_QUOTE && input[i] == '\"')
            quote_amount++;
        if (outer_quote == SINGLE_QUOTE && input[i] == '\'')
            quote_amount++;
        i++;
    }
    printf("%d\n", quote_amount);
    if (quote_amount % 2 != 0)
        return (TRUE);
    return (FALSE);
}
