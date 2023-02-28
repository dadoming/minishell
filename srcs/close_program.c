#include "../includes/minishell.h"

void free_array(char **array)
{
    int i = 0;

    if (array == NULL)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}

static void clear_core(shell_t *mini);

/* Clears all memory created by the program, still leaves readline's
    library allocated memory reachable but with no leaks. */
void close_program(shell_t *mini)
{
    clear_looped_values(mini);
    clear_core(mini);
    rl_erase_empty_line = 1;
    rl_clear_history();
    free(mini);
    return ;
}

static void clear_core(shell_t *mini)
{
    if (mini->arg_list != NULL)
        free_list(&mini->arg_list);
    if (mini->core->home != NULL)
        free(mini->core->home);
    int i = 0;
    if(mini->core->env_p != NULL)
    {
        while (mini->core->env_p[i])
        {
            free(mini->core->env_p[i]);
            i++;
        }
        free(mini->core->env_p);
    }
    free(mini->core);
}
