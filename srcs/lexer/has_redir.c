#include "../../includes/minishell.h"

static int redir_found(t_list **lst, char *str, int i, char redir_sign);
static int check_error_input(char *str, int i, char redir_sign);
static int is_redir(char *str, int i);

static int is_redir(char *str, int i)
{
    if (str[i] == '>' || str[i] == '<' || str[i] == '|')
        return (1);
    return (0);
}

static void assign_outer(char c, int *outer_quote)
{
    if (c == '\'')
        *outer_quote = SINGLE_QUOTE;
    if (c == '\"')
        *outer_quote = DOUBLE_QUOTE; 
}

int has_redir(shell_t *mini)
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
            if (quote == NO_QUOTE && string()->_search(REDIRECT, aux->token[i]) != NULL)
            {
                if (redir_found(&aux, aux->token, i, aux->token[i]) == 1)
                    return (1);
                break;
            }
            i++;
        }
        i = 0;
        aux = aux->next;
    }
    return (0);
}

static int redir_found(t_list **lst, char *str, int i, char redir_sign)
{
    t_list *aux;
    int len;

    if (check_error_input(str, i, redir_sign) == 1)
        return (1);
    aux = (*lst)->next;
    len = string()->_length(str);
    if ((i == 0 && string()->_compare_n(str, ">>", len) == 0) || 
        (i == 0 && string()->_compare_n(str, "<<", len) == 0) ||
        (i == 0 && string()->_compare_n(str, "|", len) == 0) ||
        (i == 0 && string()->_compare_n(str, ">", len) == 0) ||
        (i == 0 && string()->_compare_n(str, "<", len) == 0))
    {
        if (aux == NULL)
        {
            if (next_node_is_redirect(NULL) == 1)
                return (1);
        }
        if (next_node_is_redirect(aux->token) == 1)
            return(1); 
    }
    else if (i == 0)
        redirect_at_beggining(str, i, lst, aux);
    else
        redirect_at_middle_or_end(str, i, lst, aux);
    return (0);
}

static int check_error_input(char *str, int i, char redir_sign)
{
    int j;

    j = i;
    while (is_redir(str, j) == 1)
        j++;
    if (j == i + 1)
        return (0);
    else if (j == i + 2 && str[j - 1] == redir_sign && redir_sign != '|')
        return (0);
    else
    {
        if (j == i + 2 && str[j - 1] == '|')
            string()->_putstring_n_fd(\
            "I was not programmed to do that redirection because it was not asked!", 2);
        else 
            print_error(NULL, str[j - 1]);
        return (1);
    }
}
