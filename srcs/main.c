#include "../includes/minishell.h"

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

int check_input(int argc, char** argv)
{
    return (argc == 1 && string()->_compare_n(argv[0], "./minishell", 12) == 0);
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
/*
void execute_line(char *buff)
{
    pid_t execution;

    execution = fork();

}
*/

void close_program()
{
    if(mini()->var->logname)
        free(mini()->var->logname);
    if(mini()->var->path)
        free(mini()->var->path);
    if(mini()->var->cwd)
        free(mini()->var->cwd);
}

static char* prompt_string(void)
{
    char cwd[256];

    if (chdir("/tmp") != 0)
        perror("chdir() error()");
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return ("minishell >$ ");
    }
    else
        // add color to string.
}

int main(int argc, char** argv, char** envp)
{
    if(check_input(argc, argv) == FALSE)
        return (printf("Wrong Input. Enter ./minishell\n"));

    if(init(envp) != FALSE)
    {
        close_program();
        return (1);
    }

    char *buffer = NULL;
    while (1)
    {
        buffer = readline(prompt_string());
        if(string()->_length(buffer) > 0)
        {
            add_history(buffer);
            //execute_command(buffer);
        }
        if(string()->_compare(buffer, "exit") == 0)
        {
            free(buffer);
            break;
        }
        free(buffer);
    }

    return (0);
}
