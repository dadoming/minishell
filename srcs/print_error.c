#include "../includes/minishell.h"

void print_error(char *command)
{
    if (command)
    {
        string()->_putstring_n_fd("minishell: ", 2);
        string()->_putstring_n_fd(command, 2);
        string()->_putstring_n_fd(": ", 2);
        string()->_putstring_n_fd(strerror(errno), 2);
    }
}
