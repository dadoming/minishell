#include "../../includes/minishell.h"

int	heredoc(char *eof, shell_t *mini)
{
	int		file;
	char	*buffer;

	file = open(".heredoc_storer", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
	{
		print_normal_error("heredoc");
        return (1);
	}
    mini->here_doc = 1;
	while (1)
	{
		buffer = readline("> ");
		if (string()->_same_word(eof, buffer, string()->_length(eof)))
			break ;
		buffer = string()->_append(&buffer, "\n");
		write(file, buffer, string()->_length(buffer));
		free(buffer);
	}
	free(buffer);
	close(file);
	return (0);
}
