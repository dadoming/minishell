#include "../../includes/minishell.h"

int get_args_size(t_list *arg_list)
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
        tmp = tmp->next;
        i++;
    }
    printf("%d\n", i);
    return (i);
}

char **get_args(t_list **arg_list)
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
        arg[i] = string()->_duplicate((*arg_list)->token);
        *arg_list = (*arg_list)->next;
        i++;
    }
    return (arg);
}

void build_ast(t_list *lst, shell_t *mini)
{
    t_cmdline *cmd_line;
    t_list *aux;

    aux = lst;
    cmd_line = malloc(sizeof(t_cmdline));
    mini->cmdline = cmd_line;
    while (aux)
    {
        cmd_line->cmd = string()->_duplicate(aux->token);
        cmd_line->cmd_type = aux->type;
        cmd_line->arg = get_args(&aux);
        if (aux)
        {
            aux = aux->next;
            cmd_line->next = malloc(sizeof(t_cmdline));
            cmd_line = cmd_line->next;
        }
    }
    cmd_line->next = NULL;
}

void print_tree(t_cmdline *cmdline)
{
    t_cmdline *tmp;
    int i = 0;

    tmp = cmdline;
    while (tmp)
    {
        printf("cmd:\t%s\n", tmp->cmd);
        printf("cmd_type:\t%d\n", tmp->cmd_type);
        if (tmp->arg != NULL)
        {
            printf("arg: ");
            while (tmp->arg[i])
            {
                printf("%s\t", tmp->arg[i]);
                i++;
            }
            printf("\n");
        }
        i = 0;
        tmp = tmp->next;
    }
}