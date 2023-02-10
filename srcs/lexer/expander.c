#include "../../includes/minishell.h"

static void expand_dollars(char **content, shell_t *mini, int type);
t_list *remove_node(t_list **arg_list, t_list *node);
static char     *get_variable_name(char *str, int start);


int expander(shell_t *mini)
{
    t_list *aux;

    aux = mini->arg_list;
    while (aux != NULL)
    {
        expand_dollars(&aux->token, mini, aux->type);
        printf("%d\n", string()->_length(aux->token));
        if (string()->_length(aux->token) == 0)
        {
            aux = remove_node(&mini->arg_list, aux);
            if (aux == NULL)
            {
                if (list()->_size(mini->arg_list) == 0)
                    return (1);
                return (0);
            }
            continue;
        }
        aux = aux->next;
    }
    return (0);
}

t_list *remove_node(t_list **arg_list, t_list *node)
{
    t_list *aux;

    aux = *arg_list;
    if (*arg_list == NULL || node == NULL)
        return (NULL);
    if (*arg_list == node)
    {
        *arg_list = node->next;
        free(node->token);
        node->token = NULL;
        free(node);
        node = NULL;
        return (*arg_list);
    }
    else
    {
        while (aux->next != node)
            aux = aux->next;
        aux->next = node->next;
        free(node->token);
        node->token = NULL;
        free(node);
        node = NULL;
    }
    return (aux);
}


static void expand_dollars(char **content, shell_t *mini, int type)
{
    int i;
    int active_quote;
    char *str;

    str = *content;
    active_quote = NO_QUOTE;
    i = 0;
    if (type == DELIMITOR)
        return ;
    if (!str)
        return ;
    while (str[i] != '\0')
    {
        check_quote(&active_quote, str[i]);
        if (str[i] == '$')
        {
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
            {
                i = expand_environment(content, mini, &active_quote, \
                    get_variable_name(*content, i), i);
                str = *content;
                continue;
            }
        }
        i++;
    }
}

static char *get_variable_name(char *str, int start)
{
    char variable[131072]; // ARG_MAX
    int i;
    int j;

    j = 0;
    i = start + 1;
    if (str[i] == '?')
        return (string()->_duplicate("$?"));
    if (str[i] == '$')
        return (string()->_duplicate("$$"));
    variable[j++] = '$';
    while (str[i] != '\0' && str[i] != '$' && (check()->_is_alnum(str[i]) == 1 || str[i] == '_') \
        && str[i] != '\'' && str[i] != '\"' && (check()->_is_space(str[i]) == 0))
    {
        variable [j++] = str[i++];
    }
    variable[j] = '\0';
    return (string()->_duplicate(variable));
}

