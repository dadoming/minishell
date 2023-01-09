#include "../../includes/minishell.h"

static void store_word_list(char *rl_buffer, int *single_q, int *double_q, int *word_amount);
static void get_full_word(char *buffer, int *i, int *aux_increment, char separator);
static int check_for_ending_word(char *buffer, char delimiter);
static int check_for_ending_delimiter(char *buffer, char delimiter);

void lexer(char *rl_buffer)
{
    int single_q = 0;
    int double_q = 0;
    int word_amount = 0;

    store_word_list(rl_buffer, &single_q, &double_q, &word_amount);
    print_quote_value(single_q, double_q, word_amount);
}

static void store_word_list(char *rl_buffer, int *single_q, int *double_q, int *word_amount)
{
    int i = 0;

    while (rl_buffer[i] != '\0')
    {
        if(rl_buffer[i] == '\'')
            get_full_word(&rl_buffer[i], &i, single_q, '\'');
        else if (rl_buffer[i] == '\"')
            get_full_word(&rl_buffer[i], &i, double_q, '\"');
        else if (rl_buffer[i] != '\'' && rl_buffer[i] != '\"' && \
                (check()->_is_space(rl_buffer[i]) == FALSE))
        {
            get_full_word(&rl_buffer[i], &i, word_amount, ' ');
        }
        else
            i++;
    }
}

static void get_full_word(char *buffer, int *i, int *aux_increment, char separator)
{
    int end;
    
    if (buffer[0] == '\'' || buffer[0] == '\"')
        end = check_for_ending_delimiter(buffer, separator);
    else
        end = check_for_ending_word(buffer, separator) - 1;
    while (check()->_is_space(buffer[end + 1]) == FALSE && buffer[end + 1] != '\0')
    {
        if (buffer[end + 1] == '\'')
            end += check_for_ending_delimiter(&buffer[end + 1], '\'') + 1;
        else if (buffer[end + 1] == '\"')
            end += check_for_ending_delimiter(&buffer[end + 1], '\"') + 1;
        else if (check()->_is_ascii(buffer[end + 1]) == TRUE)
        {
            end += check_for_ending_word(&buffer[end + 1], ' ');
        }
        else
            break;
    }
    list()->_add_back(&mini()->arg_list, string()->_substr(buffer, 0, end + 1));
    (*i) += end + 1;
    (*aux_increment)++;
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

static int check_for_ending_word(char *buffer, char delimiter)
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
        if (buffer[i] == delimiter)
        {
            return (i);
        }
        i++;
    }
    if (buffer[i] == '\0')
        return (i);
    return (0);
}
