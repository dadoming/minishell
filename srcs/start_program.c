#include "../includes/minishell.h"

void helper_print()
{
    printf("%s\n", rl_line_buffer);
    free(mini()->var.cwd);
    mini()->var.cwd = getcwd(NULL,0);
    printf("cwd : %s\n", mini()->var.cwd);
    printf("argc: %d\n", mini()->arg_c);
    printf("%s\n", ttyname(STDIN_FILENO));
    printf("%d\n", ttyslot());
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
    return (string()->_split(buffer, ' '));
}

void get_input(char **buffer)
{
    *buffer = readline(mini()->prompt);
    if(string()->_length(*buffer) > 0)
    {
        add_history(*buffer);
        int i = 0;
        mini()->arg_v = separate_input(buffer[0]);
        mini()->arg_c = i + 1;
    }
}

void clear_looped_values(char **buffer)
{
    free(*buffer);
    free(mini()->prompt);
    int i = 0;
    while (mini()->arg_v[i])
        free(mini()->arg_v[i++]);
}

void start_program(void)
{
    char *buffer;

    buffer = NULL;
    while (1)
    {
        print_prompt();
        get_input(&buffer);
        if (string()->_compare("exit", rl_line_buffer) == 0)
        {
            free(rl_line_buffer);
            clear_looped_values(&buffer);
            break;
        }
        if(mini()->arg_c > 0)
        {
            cd();
            pwd();
        }
        helper_print();
        clear_looped_values(&buffer);
        free(rl_line_buffer);
        printf("error\n");
    }
}
