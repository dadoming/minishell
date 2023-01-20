#include "../../includes/minishell.h"

int pwd(void)
{
    char c[PATH_MAX];

    getcwd(c, sizeof(c));
    if (c == NULL)
        return (1);
    printf("%s\n", c);
    return (0);
}
