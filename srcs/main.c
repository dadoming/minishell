#include "../includes/minishell.h"

char	**find_path(char **env);
void	free_tree(t_cmdline **cmdline);

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
            if (executor(mini) == 1)
                break;
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
    if (mini->cmdline != NULL)
        free_tree(&mini->cmdline);
}

/* Clears tree if exists */
void	free_tree(t_cmdline **cmdline)
{
    t_cmdline	*temp;
    int i = 0;

    if (cmdline == NULL || *cmdline == NULL)
    {
        printf("No tree to free.\n");
        return ;
    }
    while (*cmdline)
    {
        temp = (*cmdline)-> next;
        if ((*cmdline)->cmd != NULL)
            free((*cmdline)->cmd);
        (*cmdline)->cmd = NULL;
        while ((*cmdline)->arg[i])
        {
            free((*cmdline)->arg[i]);
            i++;
        }
        free((*cmdline)->arg);
        (*cmdline)->arg = NULL;
        if (*cmdline)
            free(*cmdline);
        *cmdline = temp;
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
        (*lst)->token = NULL;
		if (*lst)
            free(*lst);
		*lst = temp;
	}
}
