#include "../../includes/minishell.h"

static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red);
int echo_pwd(t_cmdline *cmdline);

void execute_command(shell_t *mini, t_cmdline *aux, t_redirection *red)
{
    char **path;
    char *command;

    path = find_path(mini->core->env_p);
    command = get_command(aux->cmd, path);
    if (command == NULL)
        print_normal_error(aux->cmd);
    else
    {
        execution(mini, aux, command, red);
        free_path(path);
        free(command);
    }
}

static void execution(shell_t *mini, t_cmdline *aux, char *command, t_redirection *red)
{
    (void)red;
    mini->pid = fork();
    if (mini->pid == 0)
    {
        if (string()->_same_word(aux->cmd, "echo", 4) || string()->_same_word(aux->cmd, "pwd", 3))
            echo_pwd(aux);
        else
        {
            //close(red->pipe_fd[0]);
            //close(red->pipe_fd[1]);
            execve(command, aux->arg, mini->core->env_p);
            print_normal_error(aux->cmd);
            exit(127);
        }
        exit(0);
    }

}

int echo_pwd(t_cmdline *cmdline)
{
    if (string()->_same_word(cmdline->cmd, "echo", 4))
	{
		echo(cmdline->arg);
		return (1);
	}
	else if (string()->_same_word(cmdline->cmd, "pwd", 3))
	{
		pwd();
		return (1);
	}
    return (0);
}

