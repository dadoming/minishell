#include "../../includes/minishell.h"

static void remove_word(char *str, int start, int end);
char *remove_unexistent(char *str, int quote, int end, int start);
extern int g_exit_status;



int expand_environment(char **content, shell_t *mini, int *active_quote, char *variable)
{
    if (string()->_compare(variable, "$?") == 0)
        return (expand_status(content, variable, active_quote, mini->curr_pos));
    else if (string()->_compare_n(variable, "$$", 2) == 0)
        return (expand_double_dollar(content, active_quote, variable, mini->curr_pos));
    else
        return (normal_expand(mini, content, active_quote, variable));  
}

static void remove_word(char *str, int start, int end) 
{
    int len;

    len = string()->_length(str);
    string()->_mem_move(str + start, str + end, len - end);
    str[len - (end - start)] = '\0';
}

char *remove_unexistent(char *str, int quote, int end, int start)
{
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
            while (check()->_is_space(str[end]) == 0 && str[end] != '\0' && \
                (check()->_is_alnum(str[end]) == 1 || str[end] == '_'))
                end++;
            remove_word(str, start, end);
            return (str);
        }
        start++;
    }
    return (str);
}

int next_dollar_position(char *content, int *quote, int curr_pos)
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
