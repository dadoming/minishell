#include "../../includes/minishell.h"

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
        *content = replace(content, env_variable, &mini()->core->env_p[i][env_len + 1], NO_QUOTE);
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
