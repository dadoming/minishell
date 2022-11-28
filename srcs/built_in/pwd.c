#include "../../includes/my_lib.h"

void pwd(void)
{
    if(string()->_compare_n(mini()->arg_v[0], "pwd", 3) == 0)
    {
        free(mini()->var.cwd);
        mini()->var.cwd = getcwd(NULL,0);
        printf("Current working directory is: %s\n", mini()->var.cwd);
    }
}
