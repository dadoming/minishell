#include "../../includes/minishell.h"

int allocate(char ***trimmed, char *str)
{
    int i = 0;
    int k = 0;
    int iter = 0;

    while (str[i] != '\0')
    {
        if(str[i] == '\'')
        {
            iter = check_for_ending_quote(&str[i], '\'');
            if(iter > 0)
            {
                i += iter;
                *(trimmed[k]) = malloc(sizeof(char) * (iter + 1));
            }
        }
        else if(str[i] == '\"')
        {
            iter = check_for_ending_quote(&str[i], '\"');
            if(iter > 0)
            {
                i += iter;
                *(trimmed[k]) = malloc(sizeof(char) * (iter + 1));
            }
        }
        // incomplete
        else if (check()->_is_ascii(str[i]) && !check()->_is_space(str[i]) && str[i] != '\"' && str[i] != '\'')
        {
            int j = 0;
            while (!((check()->_is_ascii(str[i]) == TRUE && !check()->_is_space(str[i])
                && (check()->_is_space(str[i + 1]) == TRUE || str[i + 1] == '\0'))))
            {
                i++;
                j++;
            }
            if (j > 0)
            {
                printf("size of word: %d\n", j + 2);
                *(trimmed[k]) = malloc (sizeof(char) * (j + 2));
                if (!*(trimmed[k]))
                    return (1);
            }
        }
        iter = 0;
        i++;
    }
    return (1);
}


void trim_string(char *str, char ***trimmed)
{
    // int i = 0;
    // int j = 0;
    // int k = 0;

    if(!allocate(trimmed, str))
    {
        return ;
    }
    *(trimmed[0][0]) = str[0];
    *(trimmed[0][1]) = str[1];
    *(trimmed[0][2]) = str[2];
    *(trimmed[0][3]) = str[3];
    *(trimmed[0][4]) = str[4];
    // while (str[i] != '\0')
    // {
    //     while (check()->_is_space(str[i]))
    //         i++;
    //     if (str[i] == '\"')
    //     {
    //         while (str[i] != '\"' && str[i] != '\0')
    //         {
    //             *(trimmed[k][j]) = str[i];
    //             i++;
    //             j++;
    //         }
    //     }
    //     else if (str[i] == '\'')
    //     {
    //         while (str[i] != '\"' && str[i] != '\0')
    //         {
    //             *(trimmed[k][j]) = str[i];
    //             i++;
    //             j++;
    //         }
    //     }
    //     else 
    //     {
    //         printf("string: %s\n", str);
    //         while (!((check()->_is_ascii(str[i]) == TRUE && !check()->_is_space(str[i])
    //             && (check()->_is_space(str[i + 1]) == TRUE || str[i + 1] == '\0'))))
    //         {
    //             printf("%d\n", i);
    //             *(trimmed[k][j]) = str[i];
    //             printf("string: %s\n", *(trimmed[k]));
    //             i++;
    //             j++;
    //         }
    //     }
    //     *(trimmed[k][j]) = '\0';
    //     k++;
    // }
}

