#include "../includes/minishell.h"

void print_node(void *s)
{
    printf("-> %s", (char *) s);
}

static void print_type(int s)
{
    if      ((int)s == WORD) 
        printf("\t\tWORD\n");
    else if ((int)s == RED_INPUT)
        printf("\t\tRED_INPUT\n");
    else if ((int)s == HERE_DOC)
        printf("\t\tHERE_DOC\n");
    else if ((int)s == RED_OUTPUT)
        printf("\t\tRED_OUTPUT\n");
    else if ((int)s == APPEND_OUTPUT)
        printf("\t\tAPPEND_OUTPUT\n");
    else if ((int)s == INFILE)
        printf("\t\tINFILE\n");
    else if ((int)s == OUTFILE)
        printf("\t\tOUTFILE\n");
    else if ((int)s == DELIMITOR)
        printf("\t\tDELIMITOR\n");
    else if ((int)s == OUTFILE_APND)
        printf("\t\tOUTFILE_APND\n");
    else if ((int)s == PIPE)
        printf("\t\tPIPE\n");
}

void helper_print(t_list *lst)
{
    t_list *temp = lst;
    while (temp != NULL)
	{
		print_node(temp -> token);
		print_type(temp -> type);
        temp = temp -> next;
	}
    /*
    if(lst)
        list()->_iterator(lst, print_node);
    */
}
