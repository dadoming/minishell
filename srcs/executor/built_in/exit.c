#include "../../../includes/minishell.h"

int check_for_letter(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            i++;
        else
            return (0);
    }
    return (1);
}

void fun_exit(char **arg)
{
    int i;
    int status;

    i = 0;
    status = 0;
    
    while (arg[i] != 0)
        i++;
    if (i > 2)
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return ;
    }
    if (arg[1])
		status = string()->_atoi(arg[1]);
	else
		status = 0;
	printf("exit\n");
	if (!check_for_letter(arg[1]))
	{
		string()->_putstring_fd("minishell: exit: ", 2);
        string()->_putstring_fd(arg[1], 2);
        string()->_putstring_n_fd(": numeric argument required", 2);
		exit(2);
	}
	else
		exit(status);
}