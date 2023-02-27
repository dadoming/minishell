#include "../includes/minishell.h"

extern int g_exit_status;

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
            {
                clear_looped_values(mini);
                continue;
            }
            if (executor(mini, mini->cmdline) == 1)
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
    if (mini->core->free_line != NULL)
        free(mini->core->free_line);
    if (mini->core->logname != NULL)
        free(mini->core->logname);
    if (mini->core->prompt != NULL)
        free(mini->core->prompt);
    if (mini->arg_list != NULL)
        free_list(&mini->arg_list);
    if (mini->cmdline != NULL)
        free_tree(&mini->cmdline);
    if (mini->here_doc)
    {
        unlink(".heredoc_storer");
        mini->here_doc = 0;
    }
    int status;
    status = 0;
    int i = 0;
    if (mini->clear_pid == 0)
        return ;
    while (i < mini->child_num + 1)
    {
        waitpid(mini->pid[i], &status, 0);
        i++;
    }
    mini->child_num = 0;
    free(mini->pid);
    if (WIFEXITED(status))
        g_exit_status = WEXITSTATUS(status);
    mini->clear_pid = 0;
}

/* Clears tree if exists */
void	free_tree(t_cmdline **cmdline)
{
    t_cmdline	*temp;
    int i = 0;

    if (cmdline == NULL)
        return ;
    while (*cmdline)
    {
        temp = (*cmdline)-> next;
        if ((*cmdline)->cmd != NULL)
            free((*cmdline)->cmd);
        (*cmdline)->cmd = NULL;
        if ((*cmdline)->arg)
        {
            while ((*cmdline)->arg[i])
            {
                free((*cmdline)->arg[i]);
                i++;
            }
            i = 0;
            free((*cmdline)->arg);
        }
        (*cmdline)->arg = NULL;
        if ((*cmdline)->infile != NULL)
        {
            while ((*cmdline)->infile[i])
            {
                free((*cmdline)->infile[i]);
                i++;
            }
            i = 0;
            free((*cmdline)->infile);
        }
        (*cmdline)->infile = NULL;
        if ((*cmdline)->outfile != NULL)
        {
            while ((*cmdline)->outfile[i])
            {
                free((*cmdline)->outfile[i]);
                i++;
            }
            i = 0;
            free((*cmdline)->outfile);
        }
        (*cmdline)->outfile = NULL;
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
        return ;
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
