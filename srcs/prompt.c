#include "../includes/minishell.h"

static void print_prompt(void);

void get_input()
{
    print_prompt();
    mini()->out = readline(mini()->prompt);
    if (string()->_length(rl_line_buffer) > 0)
    {
        add_history(rl_line_buffer);
        mini()->arg_list = take_input(rl_line_buffer);
    }
}

static void print_prompt(void)
{
    if(mini()->logname != NULL)
    {
        mini()->prompt = string()->_duplicate(BMAG);
        mini()->prompt = string()->_append(&mini()->prompt, mini()->logname);
        mini()->prompt = string()->_append(&mini()->prompt, COLOR_RESET);
        mini()->prompt = string()->_append(&mini()->prompt, " > ");
        mini()->prompt = string()->_append(&mini()->prompt, BRED);
        mini()->prompt = string()->_append(&mini()->prompt, "minishell");
        mini()->prompt = string()->_append(&mini()->prompt, "\e[1;33m$\e[0m ");
    }
    else
    {
        mini()->prompt = string()->_duplicate(BRED);
        mini()->prompt = string()->_append(&mini()->prompt, "minishell");
        mini()->prompt = string()->_append(&mini()->prompt, COLOR_RESET);
        mini()->prompt = string()->_append(&mini()->prompt, "\e[1;33m$\e[0m ");
    }
}
