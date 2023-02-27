#include "../includes/minishell.h"

// If env has value then return value else return NULL. Example: get_env(env, "PATH")
char *get_env(char **env, char *var_name)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while (env[i])
    {
        len = string()->_length(var_name);
        if ((string()->_compare_n(env[i], var_name, len) == 0) && \
            (string()->_length_until_c(env[i], '=') == len))
        {
            return (string()->_duplicate(env[i] + len));
        }
        i++;
    }
    return (NULL);
}