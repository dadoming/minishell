#include "../../includes/minishell.h"

char **unset(t_list *lst, char **env)
{
    int i;
    int j;
    char **new_env;
    
    if (!lst->next) // Might need to be changed in the future
        return (env);
    new_env = malloc((string()->_array_length(env) + 1) * sizeof(char *));
    i = 0;
    j = 0;
    while (env[i] != 0)
    {
        if (string()->_compare_n(env[i], lst->next->token, string()->_length(lst->next->token)) == 0 && \
            string()->_length_until_c(env[i], '=') == string()->_length(lst->next->token))
        {
            free(env[i]);
            i++;
            continue;
        }
        new_env[j] = string()->_duplicate(env[i]);
        free(env[i]);
        i++;
        j++;
    }
    free(env);
    new_env[j] = 0;
    return (new_env);
}
