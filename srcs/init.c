#include "../includes/minishell.h"

void get_envp(char **envp)
{
    int     i;
    int     len;
    char    *aux;

    i = 0;
    len = 0;
    while (envp[i])
        i++;
    mini()->var.env_p = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(envp[i])
    {
        len = string()->_length(envp[i]);
        aux = string()->_copy_until(envp[i], len);
        mini()->var.env_p[i] = aux;
        i++;
    }
    mini()->var.env_p[i] = 0;
}

int init(char **envp)
{
    //variable struct init
    if(!envp)
        return (FALSE);
    
    get_envp(envp);
    mini()->var.cwd = getcwd(0, 256);
    mini()->var.logname = getenv("LOGNAME");

    //signal init
    mini()->signalset = FALSE;
    return (TRUE);
}
