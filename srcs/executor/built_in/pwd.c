#include "../../../includes/minishell.h"

extern int g_exit_status;

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
        print_normal_error("pwd");
    }
    free(buffer);
    g_exit_status = 0;
}
