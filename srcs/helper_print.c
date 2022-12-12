#include "../includes/minishell.h"

void print_node(void *s)
{
    printf("%s\n", (char *) s);
}

void print_quote_value(int single_q, int double_q)
{
    printf("\' \' -> %d\n", single_q);
    printf("\" \" -> %d\n", double_q);
}

void helper_print()
{
    int i = 0;
    while (mini()->trimmed[i] != 0)
    {
        printf("%s\n", mini()->trimmed[i]);
        i++;
    }
    //if(mini()->arg_list)
      //  list()->_iterator(mini()->arg_list, print_node);

}

