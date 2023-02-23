#include "../../../includes/minishell.h"

// 0 for no option, 1 for -n, 2 for invalid option
static int validate_option(char *option)
{
    if (option[0] == '-' && option[1] == 'n' && option[2] == '\0')
        return (1);
    return (0);
}

static void perform_echo(int n, char **args, int i)
{
    while (args[i])
    {
        string()->_putstring_fd(args[i], STDOUT_FILENO);
        i++;
        if (args[i])
            string()->_putchar_fd(' ', STDOUT_FILENO);
    }
    if (n == 0)
        string()->_putchar_fd('\n', STDOUT_FILENO);
}

//  -n means do not output the trailing newline
int echo(char **args)
{
    int n;

    n = 0;
    if (args[1] == NULL)
    {
        printf("\n");
        return (0);
    }
    if (args[1][0] == '-')
        n = validate_option(args[1]);
    if (n == 1)
        perform_echo(n, args, 2);
    else
        perform_echo(n, args, 1);
    return (0);
}
