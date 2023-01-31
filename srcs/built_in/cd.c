#include "../../includes/minishell.h"

/*
    if no HOME found and no path/args given then print error:
        bash: cd: HOME not set
    if HOME found and no path/args given then change to HOME
    if path/args given then change to path/args
*/

void cd(t_list *lst, char **env)
{
    char *home;

    home = get_env(env, "HOME");
    if (!lst->next && !home)
        string()->_putstring_n_fd("minishell: cd: HOME not set\n", 2); // Make error function
    else if (!lst->next && home)
    {
        printf("Changed to HOME: %s\n", home);
        chdir(home);
    }

    return;
}