#include "../includes/minishell.h"

void print_error(char *command, char c)
{
    if (command)
    {
        string()->_putstring_fd("minishell: ", 2);
        string()->_putstring_fd(command, 2);
        string()->_putstring_fd(": ", 2);
        string()->_putstring_n_fd(strerror(errno), 2);
    }
    if (c == '\n')
    {
        string()->_putstring_fd("minishell: syntax error near unexpected token `", 2);
        string()->_putstring_fd("newline", 2);
        string()->_putstring_n_fd("'", 2);
    }    
    else if (c)
    {
        string()->_putstring_fd("minishell: syntax error near unexpected token `", 2);
        string()->_putchar_fd(c, 2);
        string()->_putstring_n_fd("'", 2);
    }
}
