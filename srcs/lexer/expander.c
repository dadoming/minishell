#include "../../includes/minishell.h"

//static int check_quote(int *active_quote, char c);
char *expand_dollar(char **arg_pointer, int checkpoint);
void expand_values(void *token);
char *replace(const char *if_this_has, char *this, char *to_replace);

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
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
            {
                content = expand_dollar(&content, i);
                i = 0;
                printf("%s\n", content);
            }
            else
            {
                printf("Single Quote -> Take off quotes\n");
                i++;
            }
        }
        i++;
    }
}



char *expand_dollar(char **aux, int i)
{
    char *content = *aux;
    
    char env_var[9999];

    int i = 0;
    int len;
    while (mini()->core->env_p[i])
    {
        env_var[0] = '$';
        len = string()->_length_until_c(mini()->core->env_p[i], '=');
        env_var = string()->_copy_until(&env_var[1], len);
        
    }
    
    replace(mini()->arg_list, )
}


/*
char *expand_dollar(char **arg_pointer, int checkpoint)
{
    char *env_value = NULL;
    char *content = *arg_pointer;

    int i = 0;
    int checkpoint = string()->_length_until_c(content, '$');
    int len = checkpoint + 1;
    while (content[len] != '\0' && check()->_is_space(content[len]) == FALSE && \
            check()->_is_meta_char(content[len]) == FALSE && content[len + 1] != '\'' && 
            content[len + 1] != '\"')
    {
        len++;
    }

    while (mini()->core->env_p[i] != 0)
    {
        if(string()->_compare_n(mini()->core->env_p[i], &content[checkpoint + 1], len - checkpoint) == 0)
        {
            printf("Compared well\n");
            env_value = string()->_duplicate(&mini()->core->env_p[i][len - checkpoint + 1]);
            printf("%d env_value = %s\n", i, env_value);
            break;
        }
        i++;
    }



    char* strC  = string()->_copy_until(content, checkpoint);
    strC        = string()->_append(&strC, env_value);
    strC        = string()->_append(&strC, &content[len + 1]);
    free(content);
    printf("%s\n", strC);

    return (strC);
}
*/


void expander(void)
{
    list()->_iterator(mini()->arg_list, expand_values);
    
    printf("%s\n", replace("abcdddef   fpr     fpr", "fpr", "1"));
}

char *replace(const char *if_this_has, char *this, char *to_replace)
{
    char ret[9999];
    int  i;
    int  j;
    
    int size = string()->_length(this); 
    i = 0;
    while (*if_this_has)
    {
        if(this[0] == *if_this_has && string()->_compare_n(if_this_has, this, size) == 0)
        {
            j = 0;
            while (to_replace[j] != '\0')
            {
                ret[i++] = to_replace[j++];
            }
            if_this_has += size;
        }
        else
        {  
            ret[i] = *if_this_has++;
            i++;
        }
    }
    ret[i] = '\0';
    return (string()->_duplicate(ret));
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
