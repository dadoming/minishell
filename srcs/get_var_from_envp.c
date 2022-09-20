#include "../includes/minishell.h"

/*
    This function gets a variable name from the envp.
        -> *envv        - is the whole string
        -> prelimiter   - is the character that comes before the 'to be returned' word
        -> delimiter    . is the character that comes after

    There might be an easier way to do it!
*/

static int count_size(char *envv, char delimiter)
{
    int i = 0;

    while (envv[i] != delimiter)
    {
        i++;
    }
    return (i);
}

char *get_var_from_envp(char *envv, char prelimiter, char delimiter)
{
    char *str;
    int i;
    int j;
    int n;
    
    i = 0;
    str = NULL;
    if(!envv)
        return (0);
    if(prelimiter)
        while (envv[i] != prelimiter)
            i++;
    i++;
    n = count_size(&envv[i], delimiter);
    str = malloc (sizeof(char) * (n + 1));
    str[n] = '\0';
    j = 0;
    while (envv[i] != delimiter)
        str[j++] = envv[i++];
    return (str);
}