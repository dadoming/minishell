#include "../../includes/minishell.h"

static char* executable_in_folder(char *cmd);
static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i);
int echo_pwd(shell_t *mini, t_cmdline *cmdline, int i);
extern int g_exit_status;

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    char **path;
    char *command;

    if (_is_directory(aux->cmd) == 1)
    {
        string()->_putstring_fd("minishell: ", STDERR_FILENO);
        string()->_putstring_fd(aux->cmd, STDERR_FILENO);
        string()->_putstring_n_fd(": is a directory", STDERR_FILENO);
        return ;
    }
    command = executable_in_folder(aux->cmd);
    if (command != NULL)
    {
        execution(mini, aux, command, red, i);
        free(command);
        return ;
    }
    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    if (aux->cmd != NULL && aux->cmd[0] != '\0')
        execution(mini, aux, command, red, i);
    free_path(path);
    if (command)
        free(command);
}

static char* executable_in_folder(char *cmd)
{
    char *command;
    char *path;
    
    path = getcwd(NULL, 0);
    command = string()->_append(&path, "/");
    command = string()->_append(&command, cmd);
    if (access(command, F_OK) == 0)
    {
        if (access(command, X_OK) == 0)
            return (command);
    }
    return (NULL);
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
        if (access(command, F_OK) == 0 && access(command, X_OK) != 0)
        {
            string()->_putstring_fd("minishell: ", 2);
            string()->_putstring_fd(aux->cmd, 2);
            string()->_putstring_n_fd(": Permission denied", 2);
            exit(126);
        }
        if (command == NULL)
        {
            string()->_putstring_fd(aux->cmd, 2);
            string()->_putstring_n_fd(": command not found", 2);
            g_exit_status = 127;
            exit(127);
        }
        execve(command, aux->arg, mini->core->env_p);
        print_normal_error(command);
        exit(127);
    }
    else 
    {
        signal(SIGINT, sig_block_c);
    }
}
