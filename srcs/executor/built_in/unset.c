#include "../../../includes/minishell.h"

char **unset(char **arg, char **env)
{
    char **new_env;
    int i;
    int j;
    
    if (arg[1] == NULL || !env)
        return (env);
    new_env = malloc((string()->_array_length(env) + 1) * sizeof(char *));
    j = 0;
    i = 0;
    new_env = find_and_unset(arg, env, new_env, i, j);
    return (new_env);
}

char **find_and_unset(char **arg, char **env, char **new_env, int i, int j)
{
    int len;
    
    len = string()->_length(arg[1]);
    while (env[i] != 0)
    {
        if (string()->_compare_n(env[i], arg[1], len) == 0 && \
            string()->_length_until_c(env[i], '=') == len)
        {
            free(env[i]);
            env[i] = NULL;
            i++;
            new_env[j] = string()->_duplicate(env[i]);
            j++;
            continue;
        }
        new_env[j] = string()->_duplicate(env[i]);
        free(env[i]);
        env[i] = NULL;
        i++;
        j++;
    }
    free(env);
    new_env[j] = 0;
    return (new_env);
}