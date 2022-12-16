#include "../includes/minishell.h"

static void clear_core();

/* Clears all memory created by the program, still leaves readline's
    library allocated memory reachable but with no leaks. */
void close_program(void)
{
    clear_core();
    rl_erase_empty_line = 1;
    rl_clear_history();
    return ;
}

static void clear_core()
{
    free_list(&mini()->arg_list);
    if (mini()->core->rl_returned)
        free(mini()->core->rl_returned);
    if (mini()->core->prompt)
        free(mini()->core->prompt);
    if (mini()->core->logname)
        free(mini()->core->logname);
    int i = 0;
    if(mini()->core->env_p != NULL)
    {
        while (mini()->core->env_p[i])
        {
            free(mini()->core->env_p[i]);
            i++;
        }
        free(mini()->core->env_p);
    }
    free(mini()->arg_list);
    //free(mini()->core);
}
