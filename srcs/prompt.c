#include "../includes/minishell.h"

static void print_prompt(void);

/* Prints a prompt and reads input from user. */
void prompt()
{
    print_prompt();
    mini()->core->rl_returned = readline(mini()->core->prompt);
}

static void print_prompt(void)
{
    mini()->core->logname = getenv("LOGNAME");
    if(mini()->core->logname != NULL)
    {
        mini()->core->prompt = string()->_duplicate(BMAG);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, mini()->core->logname);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, COLOR_RESET);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, " > ");
        mini()->core->prompt = string()->_append(&mini()->core->prompt, BRED);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, "minishell");
        mini()->core->prompt = string()->_append(&mini()->core->prompt, "\e[1;33m$\e[0m ");
    }
    else
    {
        mini()->core->prompt = string()->_duplicate(BRED);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, "minishell");
        mini()->core->prompt = string()->_append(&mini()->core->prompt, COLOR_RESET);
        mini()->core->prompt = string()->_append(&mini()->core->prompt, "\e[1;33m$\e[0m ");
    }
}
