#include "../../includes/minishell.h"

static char *replace(char *if_this_has, char *this, char *str_to_replace, int active_quote);
static char *copy_until(char *str, int n);

char *expand_environment(char **content)
{
    int i;
    int env_len;
    char *env_variable;
    char *aux;

    aux = string()->_duplicate(*content);
    env_variable = NULL;
    env_len = 0;
    i = 0;
    while (mini()->core->env_p[i] != 0)
    {
        env_len = string()->_length_until_c(mini()->core->env_p[i], '=');
        env_variable = copy_until(mini()->core->env_p[i], env_len);
        *content = replace(*content, env_variable, &mini()->core->env_p[i][env_len + 1], NO_QUOTE);
        free(env_variable);
        i++;
    }
    if (string()->_compare_n(aux, *content, string()->_length(*content)) == 0)
    {
        free(aux);
        return (string()->_duplicate("\0"));
    }
    free(aux);    
    return (*content);
}

static char *replace(char *if_this_has, char *this, char *str_to_replace, int active_quote)
{
    char ret[512];
    int  i;
    int  j;
    int size;

    //char *aux;
    //aux = *if_this_has;
    //*if_this_has = string()->_duplicate(aux);
    //free(aux);
    
    size = string()->_length(this);
    i = 0;
    while (*if_this_has)
    {
        if (*if_this_has == '\'' || *if_this_has == '\"')
        {
            check_quote(&active_quote, *if_this_has);
            if (active_quote == SINGLE_QUOTE)
            {
                ret[i] = *if_this_has++;
                i++;
                continue;
            }
        }
        if(string()->_compare_n(if_this_has, this, size) == 0)
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
