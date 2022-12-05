#include "../includes/minishell.h"

void helper_print()
{
    //if (rl_line_buffer != NULL)
    //    printf("%s\n", rl_line_buffer);
    printf("argc: %d\n", mini()->arg_c);
    //if(mini()->arg_v != NULL)
    //{
    //    int i = 0;
    //    printf("argv: ");
    //    if(mini()->arg_v[i] != NULL)
    //    {
    //        while (mini()->arg_v[i] != 0)
    //            printf("%s ", mini()->arg_v[i++]);
    //        printf("\n");
    //    }
    //}
    //printf("%s\n", ttyname(STDIN_FILENO));
    //printf("%d\n", ttyslot());
    
}


void get_input()
{
    readline(mini()->prompt);
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        mini()->arg_v = string()->_split(rl_line_buffer, ' ');
        int i = 0;
        while (mini()->arg_v[++i] != 0)
            continue ;
        mini()->arg_c = i;
    }
}

void clear_looped_values()
{
    if (mini()->prompt)
        free(mini()->prompt);
    if (mini()->arg_v)
    {
        int i = 0;
        mini()->arg_c = 0;
        while (mini()->arg_v[i] != 0)
        {
            free(mini()->arg_v[i]);
            i++;
        }
        //free(mini()->arg_v);
    }
}

void start_program(void)
{
    //"\C-c";
    //ignore_signal_for_shell();
    while (1)
    {
        print_prompt();
        get_input();
        if(string()->_length(rl_line_buffer) > 0)
        {
            if (string()->_compare_n("exit", mini()->arg_v[0], 4) == 0)
            {
                free(rl_line_buffer);
                break;
            }
            cd();
            pwd();
        }
        helper_print();
        clear_looped_values();
    }
}
