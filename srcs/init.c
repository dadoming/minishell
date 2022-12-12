#include "../includes/minishell.h"

static void get_envp(char **envp);

int init(char **envp)
{
    if(!envp)
        return (FALSE);
    
    get_envp(envp);
    mini()->cwd = getcwd(0, 256);
    mini()->logname = getenv("LOGNAME");
    mini()->signalset = FALSE;
    return (TRUE);
}

static void get_envp(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
        i++;
    mini()->env_p = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(envp[i])
    {
        mini()->env_p[i] = string()->_duplicate(envp[i]);
        i++;
    }
    mini()->env_p[i] = 0;
}
