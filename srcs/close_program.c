#include "../includes/minishell.h"

void close_program(void)
{
    if(mini()->var.cwd)
        free(mini()->var.cwd);
    int i = 0;
    if(mini()->var.env_p != NULL)
    {
        while (mini()->var.env_p[i])
        {
            free(mini()->var.env_p[i]);
            i++;
        }
        free(mini()->var.env_p);
    }
    
    return ;
}