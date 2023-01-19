#include "../../includes/minishell.h"

//  -n means do not output the trailing newline
int echo(void)
{
    if (mini()->arg_list->next->token[0] == '-')
    {
        if (mini()->arg_list->next->token[1] == 'n')
        {
            //without \n
        }
        else
        {
            printf("Unrecognized flag\n");
            return (1);
        }
    }
    while (mini()->arg_list->token != NULL && \
            mini()->arg_list->token == WORD)
    return (0);
}
