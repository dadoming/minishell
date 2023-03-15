#include "../../includes/minishell.h"

extern int g_exit_status;

static char* copy_until(char *str, int n)
{
    char    *dst;
    int     i;
    
    if (!str)
        return (NULL);
    i = 0;
    dst = malloc(sizeof(char) * (n + 1 + 1));
    if(!dst)
        return (NULL);
    dst[0] = '$';
    while (n-- > 0)
    {
        dst[i + 1] = str[i];
        i++;
    }
    dst[i + 1] = '\0';
    return (dst);
}

int do_the_replace(t_norm norm, shell_t *mini, char **content, int *active_quote)
{
    norm.env_value = get_env(mini->core->env_p, norm.env_variable + 1);
    if (mini->core->env_p[norm.i][norm.env_len] == '=')
        *content = replace(content, norm.env_variable, norm.env_value + 1, NO_QUOTE);
    else if (mini->core->env_p[norm.i][norm.env_len] == '\0')
        *content = replace(content, norm.env_variable, norm.env_value, NO_QUOTE);
    free(norm.env_value);
    free(norm.env_variable);
    return (next_dollar_position(*content, active_quote, mini->curr_pos));
}

int normal_expand(shell_t *mini, char **content, int *active_quote, char *variable)
{
    t_norm norm;
    
    norm.var_len = string()->_length(variable);
    norm.i = 0;
    norm.env_value = NULL;
    norm.env_len = 0;
    norm.env_variable = NULL;
    while (mini->core->env_p[norm.i] != 0)
    {
        norm.env_len = string()->_length_until_c(mini->core->env_p[norm.i], '=');
        norm.env_variable = copy_until(mini->core->env_p[norm.i], norm.env_len);
        if (string()->_compare_n(norm.env_variable, variable, norm.var_len) == 0 \
            && norm.var_len == norm.env_len + 1)
        {
            free(variable);
            return (do_the_replace(norm, mini, content, active_quote));
        }
        free(norm.env_variable);
        norm.i++;
    }
    free(variable);
    *content = remove_unexistent(*content, NO_QUOTE, 0, 0);
    return (next_dollar_position(*content, active_quote, mini->curr_pos));
}

int expand_status(char **content, char *variable, int *active_quote, int curr_pos)
{
    char *env_value;
    
    env_value = string()->_itoa(g_exit_status);
    *content = replace(content, variable, env_value, NO_QUOTE);
    free(env_value);
    return (next_dollar_position(*content, active_quote, curr_pos));
}

int expand_double_dollar(char **content, int *active_quote, char *variable, int curr_pos)
{
    *content = replace(content, variable, "", NO_QUOTE);
    return (next_dollar_position(*content, active_quote, curr_pos));
}
