#include "../../includes/minishell.h"

void printenv(char **env);
static char **set_var(char **env, char *var_name, char *var_value);

void printenv(char **env)
{
    char *var_name;
    char *var_value;

    int i = 0;
    while (env[i] != 0)
    {
        var_name = string()->_copy_until(env[i], string()->_length_until_c(env[i], '='));;
        var_value = string()->_search(env[i], '=');
        printf("declare -x %s", var_name);
        if (var_value)
            printf("=\"%s\"\n", var_value + 1);
        else
            printf("\n");
        free(var_name);
        i++;
    }
    return ;
}

static char **set_var(char **env, char *var_name, char *var_value)
{
    int i = 0;
    while (env[i])
    {
        if (string()->_compare_n(env[i], var_name, string()->_length(var_name)) == 0)
        {
            if (var_value)
                substitute_env_var(&env[i], var_name, var_value);
            return (env);
        }
        i++;
    }
    if (!var_value)
        var_value = "";
    env = add_to_end_of_env(env, var_name, var_value);
    return (env);
}

char** export(t_list *lst, char **env)
{
    char *var_name;
    char *var_value;

    var_name = NULL;
    if (lst->next != NULL)
    {
        var_name = string()->_copy_until(lst->next->token, string()->_length_until_c(lst->next->token, '='));
        var_value = string()->_search(lst->next->token, '=');
    }
    if (!var_name)
    {
        printenv(env);
        return (env);
    }
    if (var_name)
        env = set_var(env, var_name, var_value);
    free(var_name);
    return (env);
}
