#include "../../includes/minishell.h"

static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i);
extern int g_exit_status;

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    char **path;
    char *command;

    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    execution(mini, aux, command, red, i);
    if (path)  
        free_path(path);
    if (command)
        free(command);
}

static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i)
{
    (void)red;
    mini->pid[i] = fork();
    if (mini->pid[i] == 0)
    {
        if (command == NULL)
        {
            string()->_putstring_fd(aux->cmd, 2);
            string()->_putstring_n_fd(": command not found", 2);
            g_exit_status = 127;
            exit(127);
        }
        execve(command, aux->arg, mini->core->env_p);
        string()->_putstring_fd(aux->cmd, 2);
        string()->_putstring_n_fd(": command not found", 2);
        exit(127);
    }
}
