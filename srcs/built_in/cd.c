#include "../../includes/minishell.h"

/*
    if no HOME found and no path/args given then print error:
        bash: cd: HOME not set
    if HOME found and no path/args given then change to HOME
    if path/args given then change to path/args
*/

char *my_getenv(const char *name, char **env)
{
    int len;
    int i = 0;

    len = string()->_length(name);
    while (env[i] != NULL)
    {
        if (string()->_compare_n(env[i], name, len) == 0 && env[i][len] == '=')
            return &env[i][len + 1];
        i++;
    }
    return NULL;
}

void    relabspath(char *path)
{
    if (chdir(path) != 0)
        print_error("cd");
}

char *my_strrchr( char *str, char c)
{
    char *res;

    res = NULL;
    while (*str != '\0')
    {
        if (*str == c)
            res = str;
        str++;
    }
    return res;
}

void cd(t_list *lst, char **env)
{
    char *home;
    char *dirname;
    char *last_slash;

    home = my_getenv("HOME", env);
    if (!lst->next && !home)
        print_error("cd");
    else if (!lst->next && home)
        chdir(home);
    else if(string()->_same_word(lst->next->token, "..", 2))
    {
        dirname = my_getenv("PWD", env);
        last_slash = my_strrchr(dirname, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0';
            chdir(my_getenv("PWD", env));
        }
    }
    else if(string()->_same_word(lst->next->token, ".", 1))
        chdir(my_getenv("PWD", env));
    else
        relabspath(lst->next->token);
    return;
}