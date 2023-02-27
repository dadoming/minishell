#include "../../../includes/minishell.h"

char            **add_to_end_of_env(char **env_p, char *var_name, char *var_value);
void            substitute_env_var(char **env_p, char *var_name, char *var_value);
static char **fill_new_value(char **new_env, int i, char *var_name, char *var_value);

char** export(char **arg, char **env_p)
{
    char *var_name;
    char *var_value;

    var_name = NULL;
    if (arg[1] != NULL)
    {
        if (check()->_is_alpha(arg[1][0]) == 0 && arg[1][0] != '_')
        {
            print_error(arg[1]);
            return (env_p);
        }
        var_name = string()->_copy_until(arg[1], string()->_length_until_c(arg[1], '='));
        var_value = string()->_search(arg[1], '=');
    }
    if (!var_name)
    {
        env(env_p, 1);
        return (env_p);
    }
    if (var_name)
        env_p = set_var(env_p, var_name, var_value);
    free(var_name);
    return (env_p);
}

char **set_var(char **env_p, char *var_name, char *var_value)
{
    int i = 0;
    while (env_p[i])
    {
        if (string()->_compare_n(env_p[i], var_name, string()->_length(var_name)) == 0 && \
            string()->_length_until_c(env_p[i], '=') == string()->_length(var_name))
        {
            if (var_value)
                substitute_env_var(&env_p[i], var_name, var_value);
            return (env_p);
        }
        i++;
    }
    if (!var_value)
        var_value = "\0";
    env_p = add_to_end_of_env(env_p, var_name, var_value);
    return (env_p);
}

void substitute_env_var(char **env_p, char *var_name, char *var_value)
{
    int i = 0;
    int j = 0;
    char *new_env;

    new_env = malloc(sizeof(char) * (string()->_length(var_name) + string()->_length(var_value) + 2));
    while (var_name[j])
    {
        new_env[j] = var_name[j];
        j++;
    }
    while (var_value[i])
    {
        new_env[j] = var_value[i];
        j++;
        i++;
    }
    new_env[j] = '\0';
    free(*env_p);
    *env_p = new_env;
}

static char **fill_new_value(char **new_env, int i, char *var_name, char *var_value)
{
    int j;
    int k;

    j = 0;
    k = 0;
    new_env[i] = malloc(sizeof(char) * \
        (string()->_length(var_name) + string()->_length(var_value) + 2));
    while (var_name[j])
    {
        new_env[i][j] = var_name[j];
        j++;
    }
    while (var_value[k] != '\0')
    {
        new_env[i][j] = var_value[k];
        j++;
        k++;
    }
    new_env[i][j] = '\0';
    new_env[i + 1] = NULL;
    return (new_env);
}

char **add_to_end_of_env(char **env_p, char *var_name, char *var_value)
{
    int i;
    char **new_env;

    i = 0;
    new_env = malloc(sizeof(char *) * (string()->_array_length(env_p) + 2));
    while (env_p[i])
    {
        new_env[i] = string()->_duplicate(env_p[i]);
        free(env_p[i]);
        i++;
    }
    new_env = fill_new_value(new_env, i, var_name, var_value);
    free(env_p);
    return (new_env);
}
