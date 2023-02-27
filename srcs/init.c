#include "../includes/minishell.h"
#include "../includes/g_var.h"

static void init_core(shell_t *mini, char **envp);

/* Initializes minishell terminal values */
int init(shell_t **mini, char **envp)
{
    g_exit_status = errno;
    if(!envp)
        return (FALSE);
    *mini = malloc(sizeof(shell_t));
    (*mini)->clear_pid = 0;
    if (!mini)
        return (FALSE);
    (*mini)->core = malloc(sizeof(t_core));
    if(!(*mini)->core)
        return (FALSE);
    init_core(*mini, envp);
    (*mini)->signalset = FALSE;
    (*mini)->cmdline = NULL;
    return (TRUE);
}

static void init_core(shell_t *mini, char **envp)
{
    int     i;

    i = 0;
    while (envp[i])
        i++;
    mini->core->env_p = malloc(sizeof(char*) * (i + 1));
    i = 0;
    while(envp[i])
    {
        mini->core->env_p[i] = string()->_duplicate(envp[i]);
        i++;
    }
    mini->arg_list = NULL;
    mini->child_num = 0;
    mini->core->env_p[i] = 0;
    mini->core->logname = NULL;
    mini->core->home = string()->_duplicate(getenv("HOME"));
    mini->core->prompt = NULL;
    mini->core->free_line = NULL;
    mini->here_doc = 0;
}
