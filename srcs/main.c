#include "../includes/minishell.h"

int check_input(int argc, char** argv)
{
    return (argc == 1 && ft_strncmp(argv[0], "./minishell", 12) == 0);
}

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

int main(int argc, char** argv, char **envp)
{
    (void)envp;
    if(check_input(argc, argv) == FALSE)
        return (0);

    mini()->var = malloc(sizeof(variables_t));
    mini()->var->session_manager_name = get_var_from_envp(getenv("SESSION_MANAGER"), '/', ':');
    mini()->var->username = getenv("LOGNAME");

    int file;
    file = open("recent_history.txt", O_CREAT | O_APPEND | O_WRONLY, 0777); 
    char *buffer = NULL;
    while (1)
    {
        write(STDOUT_FILENO, mini()->var->username, ft_strlen(mini()->var->username));
        write(STDOUT_FILENO, "@", 1);
        write(STDOUT_FILENO, mini()->var->session_manager_name, ft_strlen(mini()->var->session_manager_name));
        write(STDOUT_FILENO, ":~$ ", 4);
        buffer = get_next_line(STDIN_FILENO);
        write(file, buffer, ft_strlen(buffer));
        free(buffer);
    }



    free(mini()->var->session_manager_name);
    free(mini()->var);
    return (0);
}