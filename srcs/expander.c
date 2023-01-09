#include "../includes/minishell.h"

/*
    This function will:
    -> Treat the values inside quotes.
      -> Assign the type of quote to the token if word.
      -> Assign a controller to the token.
    -> Expand the $ and substitute it.
*/

// static void     print_n(void *s)
// {
//     printf("%s\n", (char *) s);
// }

// static void     iterator(t_token *lst, void (*f)(void *))
// {
// 	while (lst != NULL)
// 	{
// 		f(lst->text);
// 		lst = lst->next;
// 	}
// }

// static void helper_print_expander()
// {
//     if(mini()->command->text)
//         iterator(mini()->command, print_n);
// }


void copy_and_assign_types(void)
{
    t_list *temp;
    t_token *temp2;

    temp = mini()->arg_list;
    mini()->command = malloc(sizeof(t_token));
    if (!mini()->command)
        return ;
    temp2 = mini()->command;
    while (temp->next != NULL)
    {
        temp2->text = temp->token;
        //expand_values(temp2);
        temp2->next = malloc(sizeof(t_token));
        temp2 = temp2->next;
        temp = temp->next;
    }
    temp2->text = temp->token;
    temp2->next = NULL;
}

int check_quote(int *active_quote, char c)
{
    if (*active_quote == NO_QUOTE)
    {
        if (c == '\'')
            *active_quote = SINGLE_QUOTE;
        else if (c == '\"')
            *active_quote = DOUBLE_QUOTE;
        else
            *active_quote = NO_QUOTE;
    }
    else if (*active_quote == SINGLE_QUOTE)
    {
        if (c == '\'')
            *active_quote = NO_QUOTE;
        else
            *active_quote = SINGLE_QUOTE;
    }
    else if (*active_quote == DOUBLE_QUOTE)
    {
        if (c == '\"')
            *active_quote = NO_QUOTE;
        else
            *active_quote = DOUBLE_QUOTE;
    }
    return (*active_quote);
}

// Being passed the value of the token: $LOGNAME
void expand_dollar(char *content)
{
    char *env_value = NULL;

    int len = 1;
    while (content[len] != '\0' && content[len] != '$' \
        && check()->_is_space(content[len]) == FALSE)
        len++;
    int i = 0;
    while (mini()->core->env_p[i] != 0)
    {
        if(string()->_compare_n(mini()->core->env_p[i], &content[1], len - 1) == 0)
        {
            env_value = string()->_duplicate(&mini()->core->env_p[i][len]);
            break;
        }
        i++;
    }
    printf("%s\n", env_value);
    //return (env_value);
}

void expand_values(void *token)
{
    char *content;
    int i;
    int active_quote;

    content = token;
    active_quote = NO_QUOTE;
    i = 0;
    while (content[i] != '\0')
    {   
        check_quote(&active_quote, content[i]);
        if (content[i] == '$')
        {
            printf("Found $ at %d\n", i);
            if (active_quote == DOUBLE_QUOTE || active_quote == NO_QUOTE)
                expand_dollar(&content[i]);
            else
                printf("Single Quote -> Take off quotes\n");

            i = 0;
        }
        i++;
    }
}

void treat_quotes(void *token)
{
    char *content = token;
    int i = 0;
    while (content[i] != '\0')
    {
        if (content[i] == '\'')
        {
            string()->_mem_move(&content[i], &content[i + 1], string()->_length(content) - i);
            i--;
        }
        i++;
    }
}

void expander(void)
{
    //copy_and_assign_types();
    //helper_print_expander();
    list()->_iterator(mini()->arg_list, treat_quotes);
    helper_print();
    list()->_iterator(mini()->arg_list, expand_values);

}



