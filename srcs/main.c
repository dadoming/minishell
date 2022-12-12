#include "../includes/minishell.h"

static void close_program(void);
static void clear_looped_values(void);

int main(int argc, char** argv, char** envp)
{
    (void)argv;
    if(argc != 1)
        return (printf("Wrong Input. Enter ./minishell\n"));
    if(init(envp) == TRUE)
    {
        //ignore_signal_for_shell();
        while (1)
        {
            get_input();
            helper_print();
            clear_looped_values();
        }
    }
    close_program();
    return (0);
}

static void clear_looped_values(void)
{
    if (mini()->out)
        free(mini()->out);
    if (mini()->prompt)
        free(mini()->prompt);
    if (string()->_length(rl_line_buffer) > 0)
        free(mini()->arg_v);
}

static void close_program(void)
{
    if (mini()->out)
        free(mini()->out);
    if (mini()->prompt)
        free(mini()->prompt);
    if (string()->_length(rl_line_buffer) > 0)
        free(mini()->arg_v);
    if(mini()->cwd)
        free(mini()->cwd);
    int i = 0;
    if(mini()->env_p != NULL)
    {
        while (mini()->env_p[i])
        {
            free(mini()->env_p[i]);
            i++;
        }
        free(mini()->env_p);
    }
    rl_erase_empty_line = 1;
    rl_clear_history();
    return ;
}

shell_t *mini(void)
{
    static shell_t mini;

    return (&mini);
}
