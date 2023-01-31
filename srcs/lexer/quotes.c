#include "../../includes/minishell.h"

static int  only_one_quote(char *input);
static char *treat_quotes(char *str);
static void assign_outer_quote(char c, int *outer_quote, int *quote_amount);

int quotes(shell_t *mini)
{
    t_list *aux;

    aux = mini->arg_list;
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
    return (0);
}

static char *treat_quotes(char *str)
{
    int outer_quote;
    int location;
    int i;

    location = 0;
    outer_quote = NO_QUOTE;
    i = 0;
    while (str[i] != '\0')
    {
        no_quote_quote_found(&outer_quote, str[i], &location, &i);
        remove_quote_if_quote_found(&outer_quote, str, &location, &i);
        i++;
    }
    return (str);
}

char *remove_quotes(char *str, char c, int i)
{
    while (str[i] != '\0')
    {
        if (str[i] == c)
        {
            string()->_mem_move(&str[i], &str[i + 1], string()->_length(str) - i);
            if (i > 0)
                i--;
            while (str[i] != c && str[i] != '\0')
                i++;
            string()->_mem_move(&str[i], &str[i + 1], string()->_length(str) - i);
            break;
        }
        i++;
    }
    return (str);
}

static void assign_outer_quote(char c, int *outer_quote, int *quote_amount)
{
    if (c == '\'')
        *outer_quote = SINGLE_QUOTE;
    if (c == '\"')
        *outer_quote = DOUBLE_QUOTE; 
    (*quote_amount)++;
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
            assign_outer_quote(input[i], &outer_quote, &quote_amount);
        else if ((outer_quote == DOUBLE_QUOTE && input[i] == '\"') \
            || (outer_quote == SINGLE_QUOTE && input[i] == '\''))
        {
            outer_quote = NO_QUOTE;
            quote_amount++;
        }
        i++;
    }
    if (quote_amount % 2 != 0)
        return (TRUE);
    return (FALSE);
}
