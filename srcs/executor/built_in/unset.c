#include "../../../includes/minishell.h"

char **unset(char **arg, char **env)
{
    int i;
    int j;
    char **new_env;
    
    if (arg[1] == NULL) // Might need to be changed in the future
        return (env);
    new_env = malloc((string()->_array_length(env) + 1) * sizeof(char *));
    i = 0;
    j = 0;
    int len = string()->_length(arg[1]);
    while (env[i] != 0)
    {
        if (string()->_compare_n(env[i], arg[1], len) == 0 && \
            string()->_length_until_c(env[i], '=') == len)
        {
            printf("env[i]: %s\n", env[i]);
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
