#include "../../includes/minishell.h"

static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i);
int cmd_is_directory(char *cmd);
extern int g_exit_status;

static int filepath_is_accessible(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    if (cmd_is_directory(aux->cmd) == 1)
        return (1);
    else if (access(aux->cmd, X_OK) == 0 && (aux->cmd[0] == '.' || aux->cmd[0] == '/'))
    {
        execution(mini, aux, aux->cmd, red, i);
        return (1);
    }
    else if (access(aux->cmd, F_OK) == 0 && access(aux->cmd, X_OK) != 0 && (aux->cmd[0] == '.' || aux->cmd[0] == '/'))
    {
        string()->_putstring_fd(aux->cmd, STDERR_FILENO);
        string()->_putstring_n_fd(": Permission denied", STDERR_FILENO);
        return (1);
    }
    return (0);
}

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    char *command;
    char **path;

    if (filepath_is_accessible(mini, aux, red, i) == 1)
        return ;
    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    if (command != NULL && command[0] == '/')
        execution(mini, aux, command, red, i);
    else if (string()->_search(aux->cmd, '/') != 0 && command == NULL)
    {
        string()->_putstring_fd(aux->cmd, STDERR_FILENO);
        string()->_putstring_n_fd(": No such file or directory", STDERR_FILENO);
    }
    else
    {
        string()->_putstring_fd(aux->cmd, STDERR_FILENO);
        string()->_putstring_n_fd(": command not found", STDERR_FILENO);
    }
    if (path)
        free_path(path);
    if (command)
        free(command);
}

int cmd_is_directory(char *cmd)
{
    if (check()->_is_directory(cmd) == 1)
    {
        string()->_putstring_fd("minishell: ", STDERR_FILENO);
        string()->_putstring_fd(cmd, STDERR_FILENO);
        string()->_putstring_n_fd(": is a directory", STDERR_FILENO);
        g_exit_status = 126;
        return (1);
    }
    return (0);
}


static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i)
{
    (void)red;
    mini->pid[i] = fork();
    if (mini->pid[i] == 0)
    {
        execve(command, aux->arg, mini->core->env_p);
        print_normal_error(command);
        g_exit_status = 127;
        exit(127);
    }
    else 
    {
        signal(SIGINT, sig_block_c);
    }
}
