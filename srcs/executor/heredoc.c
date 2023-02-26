#include "../../includes/minishell.h"

int file_err_heredoc(char **infile, int len, shell_t *mini, t_redirection *red)
{
	int fake_heredoc;

	dup2(red->tmp_in, 0);
	dup2(red->tmp_out, 1);
	close(red->tmp_in);
	close(red->tmp_out);
	fake_heredoc = 0;
	while (len > 0)
	{
		if (infile[len][0] == '<' && infile[len][1] == '<' && infile[len][2] == '\0')
		{
			fake_heredoc = 1;
			heredoc(infile[len + 1], mini);
			break;
		}
		len--;
	}
	return (fake_heredoc);
}

int	heredoc(char *eof, shell_t *mini)
{
	int		file;
	char	*buffer;

	file = open(".heredoc_storer", O_CREAT | O_WRONLY | O_ASYNC | O_TRUNC, 0000644);
	if (file < 0)
	{
		print_normal_error("heredoc");
        return (1);
	}
    mini->here_doc = 1;
	while (1)
	{
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
		if (string()->_compare_n(eof, buffer, string()->_length(eof)) == 0)
			break ;
		write(file, buffer, string()->_length(buffer));
		free(buffer);
	}
	free(buffer);
	close(file);
	return (0);
}
