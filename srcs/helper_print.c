#include "../includes/minishell.h"

void print_node(void *s)
{
    printf("-> %s\n", (char *) s);
}

void helper_print(t_list *lst)
{
    if(lst)
        list()->_iterator(lst, print_node);
}
