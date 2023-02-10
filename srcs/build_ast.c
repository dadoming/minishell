#include "../includes/minishell.h"

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
        if (tmp->type != WORD)
            break;
        tmp = tmp->next;
        i++;
    }
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
    arg[size] = 0;
    if (!(*arg_list))
    {
        free(arg);
        return (NULL);
    }
    while (*arg_list)
    {
        if ((*arg_list)->type == PIPE || (*arg_list)->type == RED_OUTPUT || \
            (*arg_list)->type == RED_INPUT || (*arg_list)->type == APPEND_OUTPUT || \
            (*arg_list)->type == HERE_DOC)
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
        aux = aux->next;
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
    printf("Printing tree:\n");
    while (tmp)
    {
        printf("cmd: %s\n", tmp->cmd);
        printf("cmd_type: %d\n", tmp->cmd_type);
        if (tmp->arg != NULL)
        {
            printf("arg: ");
            while (tmp->arg[i])
            {
                printf("%s ", tmp->arg[i]);
                i++;
            }
            printf("\n");
        }
        i = 0;
        tmp = tmp->next;
    }
}