#include "../includes/minishell.h"

sh_t *mini(void)
{
    static sh_t mini;

    return (&mini);
}

void helper_print()
{
    free(mini()->var.cwd);
    mini()->var.cwd = getcwd(NULL,0);
    printf("cwd : %s\n", mini()->var.cwd);
    printf("argc: %d\n", mini()->arg_c);
    
    /*
    
    int i = 0;
    printf("argv: ");
    while (mini()->arg_v[i] != 0)
        printf("%s ", mini()->arg_v[i++]);
    printf("\n");
    */
}

char **separate_input(char *buffer)
{
    (void) buffer;
    return (0);
}

void get_input(char **buffer)
{
    *buffer = readline("\e[1;33m$\e[0m ");
    if(string()->_length(*buffer) > 0)
    {
        add_history(*buffer);
    }
    mini()->arg_v = separate_input(*buffer);
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


    char *buffer = NULL;
    ignore_signal_for_shell();
    while (1)
    {
        print_prompt();
        get_input(&buffer);
        if (string()->_compare("exit", rl_line_buffer) == 0)
        {
            printf("hello\n");
            free(rl_line_buffer);
            break;
        }
        if (string()->_compare("change", rl_line_buffer) == 0)
        {
            rl_replace_line("prompt> ", 1);
            rl_on_new_line();
        }
        printf("%s\n", rl_line_buffer);
        change_d();
        helper_print();
    }
    close_program();
    return (0);
}
