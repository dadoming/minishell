#include "../includes/minishell.h"

void print_prompt(void)
{
    if(mini()->var.logname != NULL)
    {
        write(STDOUT_FILENO, BMAG, 8);
        write(STDOUT_FILENO, mini()->var.logname, string()->_length(mini()->var.logname));
        write(STDOUT_FILENO, COLOR_RESET, 5);
        write(STDOUT_FILENO, " > ", 3);
    }
    write(STDOUT_FILENO, BRED, 8);
    write(STDOUT_FILENO, "minishell", 9);
    write(STDOUT_FILENO, COLOR_RESET, 5);
}
