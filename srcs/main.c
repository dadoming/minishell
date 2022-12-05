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
    
    start_program();
    
    close_program();
    return (0);
}
