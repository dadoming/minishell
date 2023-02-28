#include "../../includes/minishell.h"

static char* executable_in_folder(char *cmd);
static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red, int i);
int echo_pwd(shell_t *mini, t_cmdline *cmdline, int i);
extern int g_exit_status;

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
    free(command);
    command = string()->_duplicate(cmd);
    return (command);
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

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red, int i)
{
    char **path;
    char *command;

    if (cmd_is_directory(aux->cmd) == 1)
        return ;
    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    if (command == NULL || access(command, F_OK) != 0)
        command = executable_in_folder(aux->cmd);
    if (command != NULL && aux->cmd[0] != '\0')
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
        print_normal_error(command);
        exit(127);
    }
    else 
    {
        signal(SIGINT, sig_block_c);
    }
}
