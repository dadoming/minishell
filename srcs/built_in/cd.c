#include "../../includes/my_lib.h"

// To change
void cd(void)
{
    if(mini()->arg_c > 0)
    {
        if(string()->_compare(mini()->arg_v[0], "cd") == 0 \
            && _is_directory(mini()->arg_v[1]) == 1)
        {
            if(chdir(mini()->arg_v[1]) == -1)
                perror("path->chdir");
            printf("pwd : %s\n", getenv("PWD"));
        }
    }
}
