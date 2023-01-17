#include "../../includes/minishell.h"

static int only_one_quote(char *input);
char *remove_quotes(char *str, char c);
char *treat_quotes(char *str);

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
        aux->token = treat_quotes(aux->token);
        aux = aux->next;
    }
    
    return (FALSE);
    // remove_double_quotes(&content, 0, 0);
}

char *treat_quotes(char *str)
{
    int outer_quote;
    int i;

    outer_quote = NO_QUOTE;
    i = 0;
    while (str[i] != '\0')
    {
        if ((outer_quote == NO_QUOTE) && (str[i] == '\"'))
        {
            str = remove_quotes(str, '\"');
            outer_quote = check_quote(&outer_quote, '\"');
        }
        if ((outer_quote == NO_QUOTE) && (str[i] == '\''))
        {
            str = remove_quotes(str, '\'');
            outer_quote = check_quote(&outer_quote, '\'');
        }
        i++;
    }
    return (str);
}

char *remove_quotes(char *str, char c)
{
    int i;
    int end;

    i = 0;
    end = 0;
    while (str[i] != '\0')
    {
        if (str[i] == c)
        {
            string()->_mem_move(&str[i], &str[i + 1], string()->_length(str) - i);
            if (i > 0)
                i--;
            end = string()->_length_until_c(str, c);
            string()->_mem_move(&str[end], &str[end + 1], string()->_length(str) - end);
        }
        i++;
    }
    return (str);
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
    if (quote_amount % 2 != 0)
        return (TRUE);
    return (FALSE);
}
