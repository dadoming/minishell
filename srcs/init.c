#include "../includes/minishell.h"

static void init_core(char **envp);
static int init_structs();

/* Initializes minishell terminal values */
int init(char **envp)
{
    if(!envp)
        return (FALSE);
    init_structs();
    init_core(envp);
    mini()->signalset = FALSE;
    return (TRUE);
}

static void init_core(char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
        i++;
    mini()->core->env_p = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(envp[i])
    {
        mini()->core->env_p[i] = string()->_duplicate(envp[i]);
        i++;
    }
    mini()->core->env_p[i] = 0;
    mini()->core->logname = NULL;
    mini()->core->prompt = NULL;
    mini()->core->rl_returned = NULL;
}

static int init_structs()
{
    mini()->core = malloc(sizeof(t_core));
    if(!(mini()->core))
        return (FALSE);
    return (TRUE);
}
