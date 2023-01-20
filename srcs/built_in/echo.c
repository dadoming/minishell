#include "../../includes/minishell.h"

// 0 for no option, 1 for -n, 2 for invalid option
static int validate_option(char *token)
{
    if (token[0] == '-' && token[1] == 'n' && token[2] == '\0')
        return (1);
    return (2);
}

static void no_option(char *token)
{
    printf("minishell: echo: %s: invalid option\n", mini()->arg_list->next->token);
    printf("echo: usage: echo [-n] [arg ...]\n");
    return (1);
}

static void perform_echo(int option, int n, t_list *temp)
{
    while (temp)
    {
        if (option == 1 && temp->next == NULL)
            break;
        printf("%s", temp->token);
        if (temp->next)
            printf(" ");
        temp = temp->next;
    }
    if (n == 0)
        printf("\n");
}

//  -n means do not output the trailing newline
int echo(void)
{
    int n;
    int option;
    t_list *temp;

    temp = mini()->arg_list;
    option = 0;
    n = 0;
    if (!temp->next)
    {
        printf("\n");
        return (0);
    }
    if (mini()->arg_list->next->token[0] == '-')    
        n = validate_option(mini()->arg_list->next->token);
    if (n == 2)
        return (no_option(mini()->arg_list->next->token));
    temp = temp->next;
    perform_echo(option, n, temp);
    return (0);
}
