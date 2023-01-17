#include "../../includes/minishell.h"

static char*    expand_dollars(char *content, int i);
static char*    expand_values(char *token);

/* This function will expand the values of the tokens if there is any
    environment variable or any other value to be expanded */ 
void expander(void)
{
    t_list *aux;

    aux = mini()->arg_list;
    while (aux != NULL)
    {
        aux->token = expand_values(aux->token);
        aux = aux->next;
    }
}

int check_quote(int *active_quote, char c)
{
    if (*active_quote == NO_QUOTE)
    {
        if (c == '\'')
            *active_quote = SINGLE_QUOTE;
        else if (c == '\"')
            *active_quote = DOUBLE_QUOTE;
        else
            *active_quote = NO_QUOTE;
    }
    else if (*active_quote == SINGLE_QUOTE)
    {
        if (c == '\'')
            *active_quote = NO_QUOTE;
        else
            *active_quote = SINGLE_QUOTE;
    }
    else if (*active_quote == DOUBLE_QUOTE)
    {
        if (c == '\"')
            *active_quote = NO_QUOTE;
        else
            *active_quote = DOUBLE_QUOTE;
    }
    return (*active_quote);
}

static char* expand_dollars(char *content, int i)
{
    if (content[i + 1] == '?')
    {
        printf("$? is used to find the return value of the last executed command.\n");
        return (content);
    }
    if (check()->_is_meta_char(content[i + 1]) == 0)
    {
        content = expand_environment(&content);
        return (content);
    }
    else 
    {
        free(content);
    }
    return (string()->_duplicate("\0"));
}

static char* expand_values(char *token)
{
    int i;
    int active_quote;

    active_quote = NO_QUOTE;
    i = 0;
    while (token[i] != '\0')
    {   
        check_quote(&active_quote, token[i]);
        if (token[i] == '$')
        {
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
            {
                token = expand_dollars(token, i);
                break;
            }
        }
        i++;
    }
    return (token);
}


