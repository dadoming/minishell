#include "../../includes/minishell.h"

static void pipe_found(t_list **lst, char *leftover, int i);
static void auxiliar(t_list **lst, char *str, t_list *aux, int i, int option);

/*
    Pipe can be found in 4 scenarios:

    1. $ echo "hello" | cat
    2. $ echo "hello"|
    3. $ echo "hello" |cat
    4. $ echo "hello"|cat

*/

static void assign_outer(char c, int *outer_quote)
{
    if (c == '\'')
        *outer_quote = SINGLE_QUOTE;
    if (c == '\"')
        *outer_quote = DOUBLE_QUOTE; 
}

void has_pipe(shell_t *mini)
{
    t_list *aux;
    int quote;
    int i;

    aux = mini->arg_list;
    quote = NO_QUOTE;
    i = 0;
    while (aux)
    {
        while (aux->token[i] != '\0')
        {
            if (quote == NO_QUOTE && (aux->token[i] == '\'' || aux->token[i] == '\"'))
                assign_outer(aux->token[i], &quote);
            else if ((quote == SINGLE_QUOTE && aux->token[i] == '\'') \
                || (quote == DOUBLE_QUOTE && aux->token[i] == '\"'))
                quote = NO_QUOTE;
            if (quote == NO_QUOTE && aux->token[i] == '|')
            {
                pipe_found(&aux, aux->token, i);
                break;
            }
            i++;
        }
        i = 0;
        aux = aux->next;
    }
}

static void pipe_found(t_list **lst, char *str, int i)
{
    t_list *aux;

    aux = (*lst)->next;
    if (i == 0 && str[1] == '\0')  // echo | lol CHECK VALID
        return ;
    if (i == 0 && str[1])          // echo |lol ya CHECK VALID
    {
        auxiliar(lst, str, aux, i, 1);
        return ;
    }
    else if (str[i + 1] == '\0')   // lol| ya CHECK VALID
    {
        auxiliar(lst, str, aux, i, 2);
        return ;
    }
    else                                // lol|lol CHECK VALID
    {
        auxiliar(lst, str, aux, i, 3);   
        return ;
    }
}

static void auxiliar(t_list **lst, char *str, t_list *aux, int i, int option)
{
    if (option == 1)
    {   
        (*lst)->next = list()->_new_node(string()->_duplicate(&str[i + 1]));
        (*lst)->token[i + 1] = '\0';
        if (aux != NULL)
            (*lst)->next->next = aux;
    }
    if (option == 2)
    {
        (*lst)->token[i] = '\0';
        (*lst)->next = list()->_new_node(string()->_duplicate("|"));
        if (aux != NULL)
            (*lst)->next->next = aux;
    }
    if (option == 3)
    {
        (*lst)->token[i] = '\0';
        (*lst)->next = _new_node(string()->_duplicate("|"));
        (*lst)->next->next = _new_node(string()->_duplicate(&str[i + 1]));
        if (aux != NULL)
            (*lst)->next->next->next = aux;
    }
}