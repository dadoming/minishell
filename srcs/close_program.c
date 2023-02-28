#include "../includes/minishell.h"

static void clear_core(shell_t **mini);

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

void close_program(shell_t **mini)
{
    clear_looped_values(mini);
    clear_core(mini);
    rl_erase_empty_line = 1;
    rl_clear_history();
    free(*mini);
    return ;
}

static void clear_core(shell_t **mini)
{
    if ((*mini)->core->home != NULL)
        free((*mini)->core->home);
    free_array((*mini)->core->env_p);
    free((*mini)->core);
}
