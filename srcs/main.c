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
    mini()->var->logname = getenv("LOGNAME");

    printf("\n%s        Welcome to minishell!%s\n\n", BYEL, COLOR_RESET);
    int file;
    file = open("recent_history.txt", O_CREAT | O_APPEND | O_WRONLY, 0777); 
    char *buffer = NULL;
    while (1)
    {
        write(STDOUT_FILENO, BRED, 8);
        write(STDOUT_FILENO, mini()->var->logname, ft_strlen(mini()->var->logname));
        write(STDOUT_FILENO, "@", 1);
        write(STDOUT_FILENO, mini()->var->session_manager_name, ft_strlen(mini()->var->session_manager_name));
        write(STDOUT_FILENO, COLOR_RESET, 5);
        write(STDOUT_FILENO, ":", 1);
        write(STDOUT_FILENO, BMAG, 8);
        mini()->var->current_working_directory = getcwd(0, 128);
        write(STDOUT_FILENO, mini()->var->current_working_directory, ft_strlen(mini()->var->current_working_directory));
        write(STDOUT_FILENO, COLOR_RESET, 5);
        write(STDOUT_FILENO, "$ ", 2);
        buffer = get_next_line(STDIN_FILENO);
        write(file, buffer, ft_strlen(buffer));
        free(buffer);
    }



    free(mini()->var->session_manager_name);
    free(mini()->var);
    return (0);
}