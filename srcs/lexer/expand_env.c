#include "../../includes/minishell.h"

static char *copy_until(char *str, int n);
static void remove_word(char *str, int start, int end);
static char *remove_unexistent(char *str, int quote);
static int next_dollar_position(char *content, int *quote, int curr_pos);
extern int g_exit_status;

int expand_environment(char **content, shell_t *mini, int *active_quote, char *variable, int curr_pos)
{
    int i;
    int env_len;
    char *env_variable;
    char *env_value = NULL;
    int var_len = string()->_length(variable);


    env_variable = NULL;
    env_len = 0;
    i = 0;
    if (string()->_compare(variable, "$?") == 0)
    {
        env_value = string()->_itoa(g_exit_status);
        *content = replace(content, variable, env_value, NO_QUOTE, 0);
        free(env_value);
        return (next_dollar_position(*content, active_quote, curr_pos));
    }
    if (string()->_compare_n(variable, "$$", 2) == 0)
    {
        *content = replace(content, variable, "$", NO_QUOTE, 0);
        return (next_dollar_position(*content, active_quote, curr_pos + 1));
    }
    while (mini->core->env_p[i] != 0)
    {
        env_len = string()->_length_until_c(mini->core->env_p[i], '=');
        env_variable = copy_until(mini->core->env_p[i], env_len);
        if (string()->_compare_n(env_variable, variable, var_len) == 0 \
            && var_len == env_len + 1)
        {
            env_value = get_env(mini->core->env_p, env_variable + 1);
            if (mini->core->env_p[i][env_len] == '=')
                *content = replace(content, env_variable, env_value + 1, NO_QUOTE, 0);
            else if (mini->core->env_p[i][env_len] == '\0')
                *content = replace(content, env_variable, env_value, NO_QUOTE, 0);
            free(variable);
            free(env_value);
            free(env_variable);
            return (next_dollar_position(*content, active_quote, curr_pos));
        }
        free(env_variable);
        i++;
    }
    free(variable);
    *content = remove_unexistent(*content, NO_QUOTE);
    return (next_dollar_position(*content, active_quote, curr_pos));
}

static void remove_word(char *str, int start, int end) 
{
    int len;

    len = string()->_length(str);
    string()->_mem_move(str + start, str + end, len - end);
    str[len - (end - start)] = '\0';
}

char *remove_unexistent(char *str, int quote)
{
    int     start;
    int     end;

    end = 0;
    start = 0;
    while (str[start] != '\0')
    {
        if (str[start] == '\'' || str[start] == '\"')
        {
            check_quote(&quote, str[start]);
            if (quote == SINGLE_QUOTE)
            {
                start++;
                continue;
            }
        }
        if (str[start] == '$' && (quote == NO_QUOTE || quote == DOUBLE_QUOTE))
        {
            end = start + 1;
            while (str[end] != ' ' && str[end] != '\0' && \
                (check()->_is_alnum(str[end]) == 1 || str[end] == '_'))
                end++;
            remove_word(str, start, end);
            return (str);
        }
        start++;
    }
    return (str);
}

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

static int next_dollar_position(char *content, int *quote, int curr_pos)
{
    while (content[curr_pos] != '\0')
    {
        if (content[curr_pos] == '\'' || content[curr_pos] == '\"')
            check_quote(quote, content[curr_pos]);
        if (content[curr_pos] == '$' && (*quote == NO_QUOTE || *quote == DOUBLE_QUOTE))
        {
            return (curr_pos);
        }
        curr_pos++;
    }
    return (curr_pos);
}
