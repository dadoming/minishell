#include "../../includes/minishell.h"

extern int g_exit_status;

static void get_full_word(char *buffer, int *i, char separator, shell_t *mini);
static int check_for_ending_word(char *buffer);

/* This function is gonna produce tokens through the input passed
    in through the readline function taking quotes into account*/
int lexer(char *rl_buffer, shell_t *mini)
{
    int i = 0;

    while (rl_buffer[i] != '\0')
    {
        if(rl_buffer[i] == '\'')
            get_full_word(&rl_buffer[i], &i, '\'', mini);
        else if (rl_buffer[i] == '\"')
            get_full_word(&rl_buffer[i], &i, '\"', mini);
        else if (rl_buffer[i] != '\'' && rl_buffer[i] != '\"' && \
                (check()->_is_space(rl_buffer[i]) == FALSE))
        {
            get_full_word(&rl_buffer[i], &i, ' ', mini);
        }
        else
            i++;
    }
    if (has_redir(mini, NO_QUOTE, 0, mini->arg_list) == 1)
    {
        g_exit_status = 1;
        return (1);
    }
    return (0);
}

static void get_full_word(char *buffer, int *i, char separator, shell_t *mini)
{
    int end;
    
    if (buffer[0] == '\'' || buffer[0] == '\"')
        end = check_for_ending_delimiter(buffer, separator);
    else
        end = check_for_ending_word(buffer) - 1;
    while (check()->_is_space(buffer[end + 1]) == FALSE && buffer[end + 1] != '\0')
    {
        if (buffer[end + 1] == '\'')
            end += check_for_ending_delimiter(&buffer[end + 1], '\'') + 1;
        else if (buffer[end + 1] == '\"')
            end += check_for_ending_delimiter(&buffer[end + 1], '\"') + 1;
        else if (check()->_is_ascii(buffer[end + 1]) == TRUE)
        {
            end += check_for_ending_word(&buffer[end + 1]);
        }
        else
            break;
    }
    list()->_add_back(&mini->arg_list, string()->_substr(buffer, 0, end + 1));
    (*i) += end + 1;
}

int check_for_ending_delimiter(char *buffer, char delimiter)
{
    int i = 1;

    while (buffer[i] != '\0')
    {
        if (buffer[i] == delimiter)
            return (i);
        i++;
    }
    return (0);
}

static int check_for_ending_word(char *buffer)
{
    int i = 0;
    int aux = 0;

    while (buffer[i] != '\0')
    {
        if (buffer[i] == '\'')
        {
            aux = check_for_ending_delimiter(&buffer[i], '\'');
            if (aux > 0)
                return (i);
        }
        if (buffer[i] == '\"')
        {
            aux = check_for_ending_delimiter(&buffer[i], '\"');
            if (aux > 0)
                return (i);
        }
        if (check()->_is_space(buffer[i]) == 1)
        {
            return (i);
        }
        i++;
    }
    if (buffer[i] == '\0')
        return (i);
    return (0);
}
