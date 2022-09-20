#include "../includes/minishell.h"

// No context needed
int check_input(int argc, char** argv)
{
    return (argc == 1 && ft_strncmp(argv[0], "./minishell", 12) == 0);
}

// Makes mini variable global
sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

// Temporary function to just exit minishell successfully
int temp_exit_shell(char *str)
{
    if(ft_strncmp(str, "exit", 4) == 0)
        return (TRUE);
    return (FALSE);
}

// Writes the prompt information on the screen and also updates current working directory information
void print_prompt()
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
}

int main(int argc, char** argv, char **envp)
{
    (void)envp;
    if(check_input(argc, argv) == FALSE)
        return (printf("Wrong Input"));

    
    mini()->var = malloc(sizeof(variables_t));
    mini()->var->session_manager_name = get_var_from_envp(getenv("SESSION_MANAGER"), '/', ':');
    mini()->var->logname = getenv("LOGNAME");

    // Makes the running minishell a child process and the father will wait for it to then close and free all memory
    pid_t shell_process, wpid;
    shell_process = fork();
    char *buffer = NULL;
    if(shell_process == 0)
    {
        printf("\n%s        Welcome to minishell!%s\n\n", BYEL, COLOR_RESET);
        int file;
        file = open("recent_history.txt", O_CREAT | O_APPEND | O_WRONLY, 0777); 
        while (1)
        {
            print_prompt();
            buffer = readline("$ ");
            write(file, buffer, ft_strlen(buffer));
            write(file, "\n", 1);
            if(temp_exit_shell(buffer) == TRUE)
                exit(0);
            free(buffer);
        }
    }

    // This makes the parent wait while the child does not finish
    int status;
    while ((wpid = wait(&status)) > 0);
    printf("\n%s        Exited Minishell!%s\n\n", BYEL, COLOR_RESET);


    // Free memory - 0 leaks for now
    free(mini()->var->session_manager_name);
    free(mini()->var);
    free(mini()->var->current_working_directory);
    if (buffer)
        free(buffer);
    
    return (0);
}