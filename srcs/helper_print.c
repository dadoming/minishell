#include "../includes/minishell.h"

void print_node(void *s)
{
    printf("%s\n", (char *) s);
}

void print_quote_value(int single_q, int double_q, int word_amount)
{
    printf("\' \' -> %d\n", single_q);
    printf("\" \" -> %d\n", double_q);
    printf("words -> %d\n", word_amount);
}

void helper_print()
{
    if(mini()->arg_list)
        list()->_iterator(mini()->arg_list, print_node);
}

