#include "../../includes/minishell.h"

static void print_export(char *var_name, char *var_value);
static void print_env(char *var_name, char *var_value);

static void print_env(char *var_name, char *var_value)
{
    if (var_value != NULL)
        printf("%s%s\n", var_name, var_value);
}

static void print_export(char *var_name, char *var_value)
{
    printf("declare -x %s", var_name);
    if (var_value)
        printf("=\"%s\"\n", var_value + 1);
    else
        printf("\n");
}

// option1 for export's declare -x, option2 for env command
void env(char **env_p, int option)
{
    char *var_name;
    char *var_value;

    int i = 0;
    while (env_p[i] != 0)
    {
        var_name = string()->_copy_until(env_p[i], string()->_length_until_c(env_p[i], '='));;
        var_value = string()->_search(env_p[i], '=');
        if (option == 1)
            print_export(var_name, var_value);
        else if (option == 2)
            print_env(var_name, var_value);
        if (var_name)
            free(var_name);
        i++;
    }
    return ;
}