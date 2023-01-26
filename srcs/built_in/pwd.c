#include "../../includes/minishell.h"

void pwd(void)
{
    char *buffer;

    buffer = getcwd(NULL, 0);
    if (buffer)
    {
        printf("%s\n", buffer);
    }
    else
    {
        string()->_putstring_n_fd("minishell: pwd: ", 2);
        string()->_putstring_n_fd(strerror(errno), 2);
    }
    free(buffer);
}
