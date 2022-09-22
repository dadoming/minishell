#include "../includes/minishell.h"

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

int check_input(int argc, char** argv)
{
    return (argc == 1 && ft_strncmp(argv[0], "./minishell", 12) == 0);
}

int init(char **envp)
{
    if(!envp)
        return (FALSE);
    mini()->var = malloc(sizeof(variables_t));
    mini()->var->env_p = malloc(sizeof(envp));
    mini()->var->env_p = envp;
    return (TRUE);
}



int main(int argc, char** argv, char** envp)
{
    (void)envp;
    if(check_input(argc, argv) == FALSE)
        return (printf("Wrong Input. Enter ./minishell\n"));

    // if(init(envp) != FALSE)
    //     return (close_program());



    return (0);
}
