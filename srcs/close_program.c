#include "../includes/minishell.h"

static void clear_core();

/* Clears all memory created by the program, still leaves readline's
    library allocated memory reachable but with no leaks. */
void close_program(void)
{
    clear_looped_values();
    clear_core();
    rl_erase_empty_line = 1;
    rl_clear_history();
    return ;
}

static void clear_core()
{
    if (mini()->arg_list != NULL)
        free_list(&mini()->arg_list);
    //if (mini()->core->prompt != NULL)
      //   free(mini()->core->prompt);
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
    free(mini()->core);
}
