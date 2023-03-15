#include "../includes/minishell.h"

extern  int  g_exit_status;

void clear_looped_values(shell_t **mini)
{
    if ((*mini)->core->free_line != NULL)
        free((*mini)->core->free_line);
    if ((*mini)->core->prompt != NULL)
        free((*mini)->core->prompt);
    if ((*mini)->arg_list != NULL)
        free_list(&((*mini)->arg_list));
    if ((*mini)->cmdline != NULL)
        free_tree(mini);
    if ((*mini)->here_doc)
    {
        unlink(".heredoc_storer");
        (*mini)->here_doc = 0;
    }
    wait_for_childs((*mini));
    (*mini)->curr_pos = 0;
}

void wait_for_childs(shell_t *mini)
{
    int status;
    int i;

    i = 0;
    status = 0;
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

void	free_tree(shell_t **mini)
{
    t_cmdline	*temp;
    
    temp = NULL;
    if ((*mini)->cmdline == NULL)
        return ;
    while ((*mini)->cmdline)
    {
        temp = (*mini)->cmdline-> next;
        if ((*mini)->cmdline->cmd)
            free((*mini)->cmdline->cmd);
        (*mini)->cmdline->cmd = NULL;
        if ((*mini)->cmdline->arg)
            free_array((*mini)->cmdline->arg);
        (*mini)->cmdline->arg = NULL;
        if ((*mini)->cmdline->infile)
            free_array((*mini)->cmdline->infile);
        (*mini)->cmdline->infile = NULL;
        if ((*mini)->cmdline->outfile)
            free_array((*mini)->cmdline->outfile);
        (*mini)->cmdline->outfile = NULL;
        if ((*mini)->cmdline)
            free((*mini)->cmdline);
        (*mini)->cmdline = temp;
    }
    (*mini)->cmdline = NULL;
}

void	free_list(t_list **lst)
{
	t_list	*temp;

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
