#include "../../includes/minishell.h"

extern int g_exit_status;
static int infile_exists(t_cmdline *cmdtree);
static int treat_infile(t_cmdline *cmdtree, t_redirection *red, shell_t *mini, int i, int fd);
int check_for_heredoc(t_cmdline *cmdtree, shell_t *mini, int last_position, t_redirection *red, int fd);
void helper_norm2(t_cmdline *cmdtree, int i, int heredoc_value, int fd);

int parse_infile(shell_t *mini, t_cmdline *cmdtree, t_redirection *red)
{
    if (infile_exists(cmdtree))
    {
        red->fd_in = treat_infile(cmdtree, red, mini, -1, 0);
        if (red->fd_in == -1)
        {
            cmdtree = cmdtree->next;
            if (cmdtree != NULL)
				executor(mini, cmdtree);
            return (-1);
        }
    }
	dup2(red->fd_in, 0);
	if (red->fd_in != -1)
		close(red->fd_in);
    return (0);
}

static int treat_infile(t_cmdline *cmdtree, t_redirection *red, shell_t *mini, int i, int fd)
{
	int heredoc_value;
	int store_last_i_value;

	heredoc_value = 0;
	store_last_i_value = 0;
	while (cmdtree->infile[++i] != 0)
	{
		store_last_i_value = i;
		if (cmdtree->infile[i][0] == '<' && cmdtree->infile[i][1] == '\0')
		{
			if (fd > 0)
				close(fd);
			fd = open(cmdtree->infile[i + 1], O_RDONLY);
			g_exit_status = 1;
			if (fd == -1)
			{
				heredoc_value = file_err_heredoc(cmdtree->infile, \
					string()->_array_length(cmdtree->infile) - 1, mini, red);
				break;
			}
		}
	}
	if (heredoc_value != 1 && fd != -1)
		fd = check_for_heredoc(cmdtree, mini, store_last_i_value, red, fd);
	helper_norm2(cmdtree, i, heredoc_value, fd);
    return (fd);
}

void helper_norm2(t_cmdline *cmdtree, int i, int heredoc_value, int fd)
{
	if (heredoc_value == 1 || fd == -1)
		print_normal_error(cmdtree->infile[i + 1]);
}




static int infile_exists(t_cmdline *cmdtree)
{
    if (cmdtree->infile != NULL)
        return (1);
    return (0);
}
