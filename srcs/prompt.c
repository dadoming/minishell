#include "../includes/minishell.h"

void print_prompt(void)
{
    if(mini()->var.logname != NULL)
    {
        mini()->prompt = string()->_duplicate(BMAG);
        mini()->prompt = string()->_append(&mini()->prompt, mini()->var.logname);
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
