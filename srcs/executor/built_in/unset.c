#include "../../../includes/minishell.h"

extern int g_exit_status;
static char **find_and_unset(char **arg, char **env, char **new_env);
static int word_found(char *word, char **array);

char **unset(char **arg, char **env)
{
    char **new_env;
    int num_deletes;
    int i;

    i = 0;
    g_exit_status = 0;
    num_deletes = 0;
    if (arg[1] == NULL || !env)
        return (env);
    while (env[i])
    {
        if (string()->_compare_n(env[i], arg[1], string()->_length_until_c(env[i], '=')) == 0)
            num_deletes++;
        i++;
    }
    new_env = (char **)malloc((sizeof(char *) * (_array_length(env) - num_deletes + 1)));
    new_env = find_and_unset(arg, env, new_env);
    free_array(env);
    return (new_env);
}

static char **find_and_unset(char **arg, char **env, char **new_env)
{
    int i;
    int j;
    int copy_index;

    i = 0;
    j = 0;
    while (env[i])
    {
        copy_index = 1;
        if (word_found(env[i], arg) == 1)
            copy_index = 0;
        if (copy_index == 1)
        {
            new_env[j] = string()->_duplicate(env[i]);
            j++;
        }
        i++;
    }
    new_env[j] = 0;
    return (new_env);
}

static int word_found(char *word, char **array)
{
    int i;

    i = 0;
    while (array[i])
    {
        if (string()->_compare_n(array[i], word, string()->_length_until_c(array[i], '=')) == 0)
            return (1);
        i++;
    }
    return (0);
}
