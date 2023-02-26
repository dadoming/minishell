#include "../../includes/minishell.h"

extern int g_exit_status;
static int infile_exists(t_cmdline *cmdtree);
static int treat_infile(t_cmdline *cmdtree, t_redirection *red, shell_t *mini);

int parse_infile(shell_t *mini, t_cmdline *cmdtree, t_redirection *red)
{
    if (infile_exists(cmdtree))
    {
        red->fd_in = treat_infile(cmdtree, red, mini);
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


int check_for_heredoc(t_cmdline *cmdtree, shell_t *mini, int last_position, t_redirection *red, int fd)
{
	int i;

	i = 0;
	while (cmdtree->infile[i] != 0)
	{
		if (i >= last_position)
			break ;
		if (cmdtree->infile[i][0] == '<' && cmdtree->infile[i][1] == '<' && \
			 cmdtree->infile[i][2] == '\0')
		{
			if (fd > 0)
				close(fd);
			if (i < last_position)
			{
				heredoc(cmdtree->infile[i + 1], mini);
				fd = open(".heredoc_storer", O_RDONLY | O_ASYNC);
				g_exit_status = 1;
				if (fd == -1)
				{
					dup2(red->tmp_in, 0);
					dup2(red->tmp_out, 1);
					close(red->tmp_in);
					close(red->tmp_out);
					print_normal_error("heredoc");
					return (-1);
				}
			}
		}
		i++;
	}
	return (fd);
}

static int treat_infile(t_cmdline *cmdtree, t_redirection *red, shell_t *mini)
{
    int i;
	int fd;
	int heredoc_value;
	int store_last_i_value;

	i = 0;
	fd = 0;
	heredoc_value = 0;
	while (cmdtree->infile[i] != 0)
	{
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
			store_last_i_value = i;
		}
		i++;
	}
	if (heredoc_value != 1 && fd != -1)
		fd = check_for_heredoc(cmdtree, mini, store_last_i_value, red, fd);
	if (heredoc_value == 1 || fd == -1)
		print_normal_error(cmdtree->infile[i + 1]);
    return (fd);
}

static int infile_exists(t_cmdline *cmdtree)
{
    if (cmdtree->infile != NULL)
        return (1);
    return (0);
}
