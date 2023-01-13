#include "../../includes/minishell.h"

/*
Here is an example of how you might send the address 
of a string variable, change the string, and then free the old string in C:

#include <stdio.h>
#include <stdlib.h>

void changeString(char** str) {
    char* old_str = *str;
    *str = strdup("new string");
    free(old_str);
}

int main() {
    char* my_string = strdup("old string");
    printf("Original string: %s\n", my_string);
    changeString(&my_string);
    printf("New string: %s\n", my_string);
    free(my_string);
    return 0;
}



*/
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


char *expand_environment(char **content)
{
    char *ret;

    ret = *content;
    ret = "LOL";
    printf("content: %s\n", ret);
    return (ret);
}

char* expand_dollars(char *content, int i)
{
    char *ret;

    ret = content;
    if (ret[i + 1] == '?')
    {
        printf("$? is used to find the return value of the last executed command.\n");
        return (ret);
    }
    if (check()->_is_alnum(ret[i + 1]) == 1)
    {
        ret = expand_environment(&ret);
        return (ret);
    }
    return (NULL);
}

void expand_values(char **token)
{
    int i;
    int active_quote;

    active_quote = NO_QUOTE;
    i = 0;
    while (*token[i] != '\0')
    {   
        check_quote(&active_quote, *token[i]);
        if (*token[i] == '$')
        {
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
            {
                *token = expand_dollars(*token, i);
                i = 0;
                active_quote = NO_QUOTE;
                break;
            }
            else
            {
                printf("Else\n");
                i++;
            }
        }
        i++;
    }
}

void expander(void)
{
    t_list *aux;

    aux = mini()->arg_list;
    while (aux != NULL)
    {
        expand_values(&aux->token);
        aux = aux->next;
    }
    helper_print();
}



/*
    Handle environment variables ($ followed by a sequence of characters)
    Handle $? which should expand to the exit status of the most recently executed foreground pipeline

                    This pointer needs to be freed
                          |                       */




/*
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
*/


/*
char* expand_dollars(char *content)
{
    int i = 0;
    char *ret = NULL;
    int env_len = 0;
    char *env_variable = NULL;
    while (mini()->core->env_p[i] != 0)
    {
        env_len = string()->_length_until_c(mini()->core->env_p[i], '=');
        env_variable = copy_until(mini()->core->env_p[i], env_len);
        ret = replace(content, env_variable, &mini()->core->env_p[i][env_len + 1], NO_QUOTE);
        free(env_variable);
        env_variable = NULL;
        i++;
    }
    printf("ret: %s\n", ret);
    return (ret);
}

char *replace(char *if_this_has, char *this, char *str_to_replace, int active_quote)
{
    char ret[512];
    int  i;
    int  j;
    int size;

    size = string()->_length(this);
    i = 0;
    while (*if_this_has)
    {
        check_quote(&active_quote, *if_this_has);
        if (active_quote == SINGLE_QUOTE)
        {
            ret[i] = *if_this_has++;
            i++;
            continue;
        }
        if(this[0] == *if_this_has && string()->_compare_n(if_this_has, this, size) == 0)
        {
            j = 0;
            while (str_to_replace[j] != '\0')
            {
                ret[i++] = str_to_replace[j++];
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

