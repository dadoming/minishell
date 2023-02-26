#include "../includes/minishell.h"

void print_normal_error(char *error)
{
    if (error)
    {
        string()->_putstring_fd("minishell: ", 2);
        string()->_putstring_fd(error, 2);
        string()->_putstring_fd(": ", 2);
        string()->_putstring_n_fd(strerror(errno), 2);
    }
}

void print_error(char *identifier)
{
    string()->_putstring_fd("minishell: export: `", 2);
    string()->_putstring_fd(identifier, 2);
    string()->_putstring_n_fd("': not a valid identifier", 2);
}

void print_syntax_error(char c)
{
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
