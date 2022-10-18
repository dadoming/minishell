#include "../includes/minishell.h"

// man 2 ioctl_tty

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

void split_args(char *buff)
{
    mini()->argcount = string()->_arg_count(buff);
    mini()->argvalue = string()->_split(buff, ' ');
}

void helper_print(int i)
{
    free(mini()->var.cwd);
    mini()->var.cwd = getcwd(0,512);
    printf("cwd : %s\n", mini()->var.cwd);
    printf("argc: %d\n", mini()->argcount);
    printf("argv: ");
    while (mini()->argvalue[i] != 0)
        printf("%s ", mini()->argvalue[i++]);
    printf("\n");
}

int main(int argc, char** argv, char** envp)
{
    (void)argv;
    // Checks execution
    if(argc != TRUE)
        return (printf("Wrong Input. Enter ./minishell\n"));

    // Inits program information
    if(init(envp) == FALSE)
    {
        close_program();
        return (1);
    }

    char *buffer = NULL;
    //ignore_signal_for_shell();
    while (1)
    {
        print_prompt();
        buffer = readline("\e[1;33m$\e[0m ");
        if(string()->_length(buffer) > 0)
            add_history(buffer);
        if(string()->_compare(buffer, "exit") == 0)
        {
            free(buffer);
            break;
        }
        
        // Gets argv and argc from minishell
        split_args(buffer);

        // Prints the input on screen
        change_d();
        helper_print(0);
        
        free(mini()->argvalue);
        free(buffer);
    }

    // Frees all memory in program
    close_program();

    return (0);
}
