#include "../../includes/minishell.h"

static int check_quote(int *active_quote, char c);

/*
    This function will:
    -> Treat the values inside quotes.
      -> Assign the type of quote to the token if word.
      -> Assign a controller to the token.
    -> Expand the $ and substitute it.

    1. Iterate through the argument.
    2. If $ found
        2.1. Check if $ is inside double quotes or no quotes, else just ignore
    3. Return to the start and take of unnecessary quotes, for that just iterate
        through the argument and once a pair of " " is found, then just take them of.
       If there is a pair ' ', check if it is inside double quotes. If it is then just
        leave them there.


*/

void expander(void)
{
    list()->_iterator(mini()->arg_list, expand_values);
    helper_print();
}

void expand_values(void *token)
{
    char *content;
    int i;
    int active_quote;

    content = token;
    active_quote = NO_QUOTE;
    i = 0;
    while (content[i] != '\0')
    {   
        check_quote(&active_quote, content[i]);
        if (content[i] == '$')
        {
            printf("Found $ at %d\n", i);
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
                expand_dollar(&content[i]);
            else
                printf("Single Quote -> Take off quotes\n");
            i = 0;
        }
        i++;
    }
}

// Being passed the value of the token: $LOGNAME
void expand_dollar(char *content)
{
    char *env_value = NULL;

    int len = 1;
    while (content[len] != '\0' && content[len] != '$' \
        && check()->_is_space(content[len]) == FALSE)
        len++;
    int i = 0;
    while (mini()->core->env_p[i] != 0)
    {
        if(string()->_compare_n(mini()->core->env_p[i], &content[1], len - 1) == 0)
        {
            env_value = string()->_duplicate(&mini()->core->env_p[i][len]);
            break;
        }
        i++;
    }
    printf("%s\n", env_value);
    //return (env_value);
}

static int check_quote(int *active_quote, char c)
{
    if (*active_quote == NO_QUOTE)
    {
        if (c == '\'')
            *active_quote = SINGLE_QUOTE;
        else if (c == '\"')
            *active_quote = DOUBLE_QUOTE;
        else
            *active_quote = NO_QUOTE;
    }
    else if (*active_quote == SINGLE_QUOTE)
    {
        if (c == '\'')
            *active_quote = NO_QUOTE;
        else
            *active_quote = SINGLE_QUOTE;
    }
    else if (*active_quote == DOUBLE_QUOTE)
    {
        if (c == '\"')
            *active_quote = NO_QUOTE;
        else
            *active_quote = DOUBLE_QUOTE;
    }
    return (*active_quote);
}



