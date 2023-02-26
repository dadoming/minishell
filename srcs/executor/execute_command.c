#include "../../includes/minishell.h"

static char* executable_in_folder(char *cmd);
static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i);
extern int g_exit_status;

static char* executable_in_folder(char *cmd)
{
    char *command;
    char *path;

    command = NULL;
    path = getcwd(NULL, 0);
    command = string()->_append(&path, "/");
    command = string()->_append(&command, cmd);
    if (access(command, F_OK) == 0)
    {
        if (access(command, X_OK) == 0)
            return (command);
        else
        {
            string()->_putstring_fd("minishell: ", STDERR_FILENO);
            string()->_putstring_fd(cmd, STDERR_FILENO);
            string()->_putstring_n_fd(": Permission denied", STDERR_FILENO);
            g_exit_status = 126;
            free(command);
            return (NULL);
        }
    }
    return (NULL);
}

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    char **path;
    char *command;

    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    if (command == NULL)
        command = executable_in_folder(aux->cmd);
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
