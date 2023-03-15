#include "../includes/minishell.h"

extern int g_exit_status;

int main(int argc, char** argv, char** envp)
{
    shell_t *mini;

    (void)argv;
    if(argc != 1)
        return (printf("Wrong Input. Enter ./minishell\n"));
    if(init(&mini, envp) == TRUE)
    {
        while (1)
        {
            signal(SIGQUIT, SIG_IGN);
		    signal(SIGINT,  sigint_handler);
            signal(SIGTERM, sigterm_handler);
            prompt(mini);
            if (evaluate(mini) == 1)
            {
                clear_looped_values(&mini);
                continue;
            }
            if (executor(mini, mini->cmdline) == 1)
                break;
            clear_looped_values(&mini);
        }
    }
    close_program(&mini);
    system("leaks minishell");
    return (0);
}

