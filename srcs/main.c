#include "../includes/minishell.h"

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

int main(int argc, char** argv, char** envp)
{
    (void)argv;
    if(argc != TRUE)
        return (printf("Wrong Input. Enter ./minishell\n"));
    if(init(envp) == FALSE)
    {
        close_program();
        return (1);
    }
    //"\C-c";
    ignore_signal_for_shell();
    start_program();
    
    close_program();
    return (0);
}
