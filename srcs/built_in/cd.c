#include "../../includes/my_lib.h"

// To change
void change_d(void)
{
    if(mini()->argc > 0)
    {
        if(string()->_compare(mini()->argvalue[0], "cd") == 0 \
            && _is_directory(mini()->argvalue[1]) == 1)
        {
            if(chdir(mini()->argvalue[1]) == -1)
                perror("path->chdir");
            printf("pwd : %s\n", getenv("PWD"));
        }
    }
}
