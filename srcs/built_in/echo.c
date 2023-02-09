#include "../../includes/minishell.h"

// 0 for no option, 1 for -n, 2 for invalid option
static int validate_option(char *token)
{
    if (token[0] == '-' && token[1] == 'n' && token[2] == '\0')
        return (1);
    return (0);
}

static void perform_echo(int option, int n, t_list *arg_list)
{
    while (arg_list)
    {
        if (option == 1 && arg_list->next == NULL)
            break;
        printf("%s", arg_list->token);
        if (arg_list->next)
            printf(" ");
        arg_list = arg_list->next;
    }
    if (n == 0)
        printf("\n");
}

//  -n means do not output the trailing newline
int echo(t_list *arg_list)
{
    int n;
    int option;

    option = 0;
    n = 0;
    if (!arg_list->next)
    {
        printf("\n");
        return (0);
    }
    if (arg_list->next->token[0] == '-')    
        n = validate_option(arg_list->next->token);
    arg_list = arg_list->next;
    if (n == 1)
        arg_list = arg_list->next;
    perform_echo(option, n, arg_list);
    return (0);
}
