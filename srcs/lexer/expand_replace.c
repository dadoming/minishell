#include "../../includes/minishell.h"

static int calculate_size(char **if_this_has, char *this, char *str_to_replace, int size, int active_quote);
static void copy_env_value(char **if_this_has, char *str_to_replace, char *ret, int *i, int size);
static void copy_value(char *ret, char **if_this_has, int *i);

char *replace(char **if_this_has, char *this, char *str_to_replace, int active_quote, int i)
{
    char    *ret;
    char    *free_mem;
    int     size;
    
    free_mem = *if_this_has;
    size = string()->_length(this);
    ret = malloc (sizeof(char) * (calculate_size(if_this_has, this, str_to_replace, size, NO_QUOTE) + 1));
    *if_this_has = free_mem;
    while (**if_this_has != '\0')
    {
        if ((**if_this_has == '\'' || **if_this_has == '\"') \
            && (check_quote(&active_quote, **if_this_has) == SINGLE_QUOTE))
        {
            ret[i] = **if_this_has;
            (*if_this_has)++;
            i++;
            continue;
        }
        if(string()->_compare_n(*if_this_has, this, size) == 0)
            copy_env_value(if_this_has, str_to_replace, ret, &i, size);
        else
            copy_value(ret, if_this_has, &i);
    }
    ret[i] = '\0';
    free(free_mem);
    return (ret);
}

static void copy_env_value(char **if_this_has, char *str_to_replace, char *ret, int *i, int size)
{
    int j;
    
    j = 0;
    while (str_to_replace[j] != '\0')
    {
        ret[(*i)++] = str_to_replace[j++];
    }
    *if_this_has += size;
}

static void copy_value(char *ret, char **if_this_has, int *i)
{
    ret[*i] = **if_this_has;
    (*if_this_has)++;
    (*i)++;
}

static int calculate_size(char **if_this_has, char *this, char *str_to_replace, int size, int active_quote)
{
    int total_return_size;

    total_return_size = 0;
    while (**if_this_has != '\0')
    {
        if ((**if_this_has == '\'' || **if_this_has == '\"') && \
            (check_quote(&active_quote, **if_this_has) == SINGLE_QUOTE))
        {
            total_return_size++;
            (*if_this_has)++;
            continue;
        }
        if (string()->_compare_n(*if_this_has, this, size) == 0 && str_to_replace)
        {
            total_return_size += string()->_length(str_to_replace);
            (*if_this_has) += size;
        }
        else
        {
            total_return_size++;
            (*if_this_has)++;
        }
    }
    return (total_return_size);
}



