#include "../includes/minishell.h"

char	**find_path(char **env);

int main(int argc, char** argv, char** envp)
{
    shell_t *mini;

    (void)argv;
    if(argc != 1)
        return (printf("Wrong Input. Enter ./minishell\n"));
    if(init(&mini, envp) == TRUE)
    {
        //ignore_signal_for_shell();
        while (1)
        {
            prompt(mini);
            if (evaluate(mini) == 1)
                break;
            
            //if (parser() == 1)
              //  break;
            clear_looped_values(mini);
        }
    }
    close_program(mini);
    return (0);
}

/* Clear all values generated by each line execution. */
void clear_looped_values(shell_t *mini)
{
    int i = 0;
    if (mini->core->free_line != NULL)
        free(mini->core->free_line);
    if (mini->core->prompt != NULL)
        free(mini->core->prompt);
    if (mini->arg_list != NULL)
        free_list(&mini->arg_list);
    if (mini->core->execution_path != NULL)
    {
        while (mini->core->execution_path[i] != 0)
        {
            free(mini->core->execution_path[i]);
            i++;
        }
        free(mini->core->execution_path);
    }
}

/* Clears list if existent. */
void	free_list(t_list **lst)
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
	{
        printf("No list to free.\n");
        return ;
    }
	while (*lst)
	{
		temp = (*lst)-> next;
        if ((*lst)->token)
            free((*lst)->token);
		if (*lst)
            free(*lst);
		*lst = temp;
	}
}
