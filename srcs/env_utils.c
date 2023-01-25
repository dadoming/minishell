#include "../includes/minishell.h"

/*
   var_name    =      var_value          
   (token1) (token2) (token3)
    subsitute(char **env, char *var_name, char *var_value)
*/

char **add_to_end_of_env(char **env, char *var_name, char *var_value);
void substitute_env_var(char **env, char *var_name, char *var_value);

void substitute_env_var(char **env, char *var_name, char *var_value)
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
    free(*env);
    *env = new_env;
}

char **add_to_end_of_env(char **env, char *var_name, char *var_value)
{
    int i = 0;
    int j = 0;
    int k = 0;
    char **new_env;

    while (env[i])
        i++;
    new_env = malloc(sizeof(char *) * (i + 2));
    i = 0;
    while (env[i])
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = malloc(sizeof(char) * (string()->_length(var_name) + string()->_length(var_value) + 1));
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

