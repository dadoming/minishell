#include "../../includes/minishell.h"

static int get_args_size(t_list *arg_list);
static char **get_args(t_list **arg_list);

t_cmdline *init_node(void)
{
    t_cmdline *cmd_line;

    cmd_line = malloc(sizeof(t_cmdline));
    cmd_line->cmd = NULL;
    cmd_line->infile = NULL;
    cmd_line->outfile = NULL;
    cmd_line->arg = NULL;
    cmd_line->next = NULL;
    return (cmd_line);
}

int build_ast(t_list *lst, shell_t *mini)
{
    t_cmdline *cmd_line;
    t_list *aux;

    aux = lst;
    cmd_line = init_node();
    mini->cmdline = cmd_line;
    while (aux)
    {
        if (aux->type == WORD)
            cmd_line->cmd = string()->_duplicate(aux->token);
        else
            return (1);
        cmd_line = get_redir(aux, cmd_line);
        cmd_line->arg = get_args(&aux);
        if (aux)
        {
            aux = aux->next;
            cmd_line->next = init_node();
            cmd_line = cmd_line->next;
        }
    }
    cmd_line->next = NULL;
    return (0);
}

static int get_args_size(t_list *arg_list)
{
    int i;
    t_list *tmp;

    if (!arg_list)
        return (0);
    tmp = arg_list;
    i = 0;
    while (tmp)
    {
        if (tmp->type == PIPE)
            break;
        if (tmp->type == WORD)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

static char **get_args(t_list **arg_list)
{
    char **arg;
    int i;
    int size;

    i = 0;
    size = get_args_size(*arg_list);
    arg = malloc(sizeof(char*) * (size + 1));
    arg[size] = NULL;
    while (*arg_list)
    {
        if ((*arg_list)->type == PIPE)
            break;
        if ((*arg_list)->type == WORD)
        {
            arg[i] = string()->_duplicate((*arg_list)->token);
            i++;
        }
        *arg_list = (*arg_list)->next;
    }
    return (arg);
}

void print_tree(t_cmdline *cmdline)
{
    t_cmdline *tmp;
    int i = 0;

    tmp = cmdline;
    while (tmp)
    {
        if (tmp->arg != NULL)
        {
            printf("\ncmds\t:\t");
            while (tmp->arg[i])
            {
                printf("%s\t", tmp->arg[i]);
                i++;
            }
            printf("\n");
            if (tmp->infile != NULL)
            {
                printf("infile\t:\t");
                i = 0;
                while (tmp->infile[i])
                {
                    printf("%s\t", tmp->infile[i]);
                    i++;
                }
                printf("\n");
            }
            if (tmp->outfile != NULL)
            {
                printf("outfile\t:\t");
                i = 0;
                while (tmp->outfile[i])
                {
                    printf("%s\t", tmp->outfile[i]);
                    i++;
                }
                printf("\n");
            }
            printf("\n");
        }
        i = 0;
        tmp = tmp->next;
    }
}
