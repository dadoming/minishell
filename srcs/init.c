#include "../includes/minishell.h"

void get_envp(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
        i++;
    mini()->var.env_p = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(envp[i])
    {
        mini()->var.env_p[i] = string()->_duplicate(envp[i]);
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
