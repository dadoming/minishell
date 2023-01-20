#include "../../includes/minishell.h"

// 0 for no flag, 1 for -n, 2 for invalid flag
int validate_flag(char *token)
{
    if (token[0] == '-' && token[1] == 'n' && token[2] == '\0')
    {
        return (1);
    }
    return (2);
}

//  -n means do not output the trailing newline
int echo(void)
{
    int n;
    int flag;
    t_list *temp;

    temp = mini()->arg_list;
    flag = 0;
    n = 0;
    if (!temp->next)
    {
        printf("\n");
        return (0);
    }
    if (mini()->arg_list->next->token[0] == '-')    
        n = validate_flag(mini()->arg_list->next->token);
    if (n == 2)
    {
        printf("minishell: echo: %s: invalid option\n", mini()->arg_list->next->token);
        printf("echo: usage: echo [-n] [arg ...]\n");
        return (1);
    }
    temp = temp->next;
    while (temp != NULL)
    {
        if (flag == 0 && n == 1)
        {
            flag = 1;
            temp = temp->next;
            continue;
        }
        printf("%s", temp->token);
        if (temp->next != NULL)
            printf(" ");
        temp = temp->next;
    }
    if (n != 1)
        printf("\n");
    return (0);
}
