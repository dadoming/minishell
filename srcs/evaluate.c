#include "../includes/minishell.h"
/*helper_print(mini->arg_list);print_tree(mini->cmdline)*/
int	evaluate(shell_t *mini)
{
	if (string()->_length(rl_line_buffer) > 0)
	{
		add_history(rl_line_buffer);
		if (lexer(rl_line_buffer, mini) == 1)
			return (1);
		define_type(mini);
		if (expander(mini) == 1)
			return (1);
		if (quotes(mini) == TRUE)
			return (1);
		if (list()->_size(mini->arg_list) > 0)
			build_ast(mini->arg_list, mini);
		return (0);
	}
	return (1);
}
