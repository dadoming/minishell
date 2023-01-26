#include "../includes/minishell.h"

// If env has value then return value
char *get_env(char **env, char *var_name)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (string()->_compare_n(env[i], var_name, string()->_length(var_name)) == 0)
        {
            return (env[i] + string()->_length(var_name));
        }
        i++;
    }
    return (NULL);
}