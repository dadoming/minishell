#include "../../includes/minishell.h"

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

static int treat_infile(t_cmdline *cmdtree, t_redirection *red, shell_t *mini)
{
    int i;
	int fd;

	i = 0;
	fd = 0;
	while (cmdtree->infile[i] != 0)
	{
		if (cmdtree->infile[i][0] == '<' && cmdtree->infile[i][1] == '\0')
		{
			if (fd > 0)
				close(fd);
			fd = open(cmdtree->infile[i + 1], O_RDONLY);
			if (fd == -1)
			{
				dup2(red->tmp_in, 0);
				dup2(red->tmp_out, 1);
				close(red->tmp_in);
				close(red->tmp_out);
				print_normal_error(cmdtree->infile[i + 1]);
				break;
			}
		}
		else if (cmdtree->infile[i][0] == '<' && cmdtree->infile[i][1] == '<' \
			&& cmdtree->infile[i][2] == '\0')
		{
			if (fd > 0)
				close(fd);
			if(heredoc(cmdtree->infile[i + 1], mini) == 0)
			{
				fd = open(".heredoc_storer", O_RDONLY);
				if (fd == -1)
				{
					dup2(red->tmp_in, 0);
					dup2(red->tmp_out, 1);
					close(red->tmp_in);
					close(red->tmp_out);
					print_normal_error("heredoc");
					break;
				}
			}
			
		}
		i++;
	}
    return (fd);
}

static int infile_exists(t_cmdline *cmdtree)
{
    if (cmdtree->infile != NULL)
        return (1);
    return (0);
}
