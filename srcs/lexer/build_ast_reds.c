#include "../../includes/minishell.h"

static int calculate_size_out(t_list *arg_list);
static int calculate_size_in(t_list *arg_list);
static t_cmdline *load_redirections(t_cmdline *tree_node, t_list *arg_list);

t_cmdline *get_redir(t_list *arg_list, t_cmdline *tree_node)
{
    int size_out;
    int size_in;

    size_out = calculate_size_out(arg_list);
    if (size_out > 0)
    {
        tree_node->outfile = malloc(sizeof (char *) * (size_out + 1));
        tree_node->outfile[size_out] = 0;
    }
    size_in = calculate_size_in(arg_list);
    if (size_in > 0)
    {
        tree_node->infile = malloc(sizeof (char *) * (size_in + 1));
        tree_node->infile[size_in] = 0;
    }
    if (size_in > 0 || size_out > 0)
        tree_node = load_redirections(tree_node, arg_list);
    return (tree_node);
}

static t_cmdline *load_redirections(t_cmdline *tree_node, t_list *arg_list)
{
    int in;
    int out;

    in = 0;
    out = 0;
    while (arg_list)
    {
        if (arg_list->type == PIPE)
            break;
        if (arg_list->type == RED_OUTPUT || arg_list->type == APPEND_OUTPUT \
            || arg_list->type == OUTFILE || arg_list->type == OUTFILE_APND)
        {
            tree_node->outfile[in] = string()->_duplicate(arg_list->token);
            in++;
        }
        if (arg_list->type == RED_INPUT || arg_list->type == HERE_DOC \
            || arg_list->type == INFILE || arg_list->type == DELIMITOR)
        {
            tree_node->infile[out] = string()->_duplicate(arg_list->token);
            out++;
        }
        arg_list = arg_list->next;
    }

    return (tree_node);
}

static int calculate_size_out(t_list *arg_list)
{
    t_list *aux;
    int i;

    i = 0;
    aux = arg_list;
    while (aux)
    {
        if (aux->type == PIPE)
            break;
        if (aux->type == RED_OUTPUT || aux->type == APPEND_OUTPUT \
            || aux->type == OUTFILE || aux->type == OUTFILE_APND)
        {
            i++;
        }
        aux = aux->next;
    }
    return (i);
}

static int calculate_size_in(t_list *arg_list)
{
    t_list *aux;
    int i;

    i = 0;
    aux = arg_list;
    while (aux)
    {
        if (aux->type == PIPE)
            break;
        if (aux->type == RED_INPUT || aux->type == HERE_DOC \
            || aux->type == INFILE || aux->type == DELIMITOR)
        {
            i++;
        }
        aux = aux->next;
    }
    return (i);
}
