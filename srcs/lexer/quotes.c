#include "../../includes/minishell.h"

static int only_one_quote(char *first, char second, char quote);

void treat_quotes(void *token)
{
    char *content;
    
    content = token;
    if (only_one_quote(&content[0], content[1], '\'') == TRUE)
        return ;
    if (only_one_quote(&content[0], content[1], '\"') == TRUE)
        return ;
    
    // remove_double_quotes(&content, 0, 0);
}

// Removes all double quotes in the sentence. Needs to be tweaked to only remove the neccessary ones
void remove_double_quotes(char **aux, int i, int end)
{
    char *content;

    content = *aux;
    while (content[i] != '\0')
    {
        if (content[i] == '\"')
        {
            string()->_mem_move(&content[i], &content[i + 1], string()->_length(content) - i);
            i--;
            end = string()->_length(content);
            while (content[end] != '\"')
            {
                end--;
                if (content[end] == '\"')
                {
                    string()->_mem_move(&content[end], &content[end + 1], string()->_length(content) - end);
                    break;
                }
                if (end == 0)
                    break;
            }
        }
        i++;
    }
}

static int only_one_quote(char *first, char second, char quote)
{
    if (*first == quote && second == '\0')
    {
        *first = '\0';
        printf("Error: Only one quote not closed\"\n");
        return (TRUE);
    }
    return (FALSE);
}
