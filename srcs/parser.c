#include "../includes/minishell.h"

/*
Iterate through the list and until PIPE or NULL
found store the tokens.
-> COMMAND or PIPE is the first token.
-> All the others are arguments until REDIRECTION or NULL.
*/


/* Located in my_lib.h
typedef struct s_list
{
    char            *token;
    struct s_list   *next;
} t_list;


Take off quotes needs to be done after this function.


int 

void create_cmdline(t_cmdline *cmdline, t_list *arg_list)
{
    while (arg_list)
    {
        while (arg_list->token)
        {
            while (REDIRECT[i] )
            {
                if (string()->_search(arg_list->token, REDIRECT[i]) != NULL)
                i++;
            }

        }
    }
}

int parser(shell_t *mini)
{
    mini->cmdline = malloc(sizeof(t_cmdline));
    
    create_cmdline(mini->cmdline, mini->arg_list);
}


*/