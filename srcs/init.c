#include "../includes/minishell.h"
#include "../includes/g_var.h"

static void init_core(shell_t *mini, char **envp);
static void set_shlvl(shell_t *mini);

/* Initializes minishell terminal values */
int init(shell_t **mini, char **envp)
{
    g_exit_status = 0;
    if(!envp)
        return (FALSE);
    *mini = malloc(sizeof(shell_t));
    if (!*mini)
        return (FALSE);
    (*mini)->core = malloc(sizeof(t_core));
    if(!(*mini)->core)
        return (FALSE);
    init_core(*mini, envp);
    (*mini)->clear_pid = 0;
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
    if (mini->core->env_p == NULL)
        return ;
    i = 0;
    while(envp[i])
    {
        mini->core->env_p[i] = string()->_duplicate(envp[i]);
        i++;
    }
    mini->core->env_p[i] = 0;
    mini->core->logname = NULL;
    mini->core->home = string()->_duplicate(getenv("HOME"));
    mini->core->prompt = NULL;
    mini->core->free_line = NULL;
    mini->arg_list = NULL;
    mini->child_num = 0;
    mini->here_doc = 0;
    mini->curr_pos = 0;
    mini->pid = NULL;
    set_shlvl(mini);
}

static void set_shlvl(shell_t *mini)
{
    char *shlvl;
    int shlvl_int;
    char *shlvl_new;
    char *value;

    shlvl = string()->_duplicate("SHLVL");
    if (shlvl == NULL)
        return ;
    shlvl_int = string()->_atoi(my_getenv("SHLVL", mini->core->env_p));
    shlvl_int++;
    shlvl_new = string()->_itoa(shlvl_int);
    if (shlvl_new == NULL)
        return ;
    value = string()->_duplicate("=");
    value = string()->_append(&value, shlvl_new);
    mini->core->env_p = set_var(mini->core->env_p, shlvl, value);
    free(shlvl_new);
    free(shlvl);
    free(value);
}
