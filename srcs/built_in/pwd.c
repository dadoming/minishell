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
        print_error("pwd");
    }
    free(buffer);
}
