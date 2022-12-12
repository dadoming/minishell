#include "../../includes/minishell.h"

void trim_string(char *str)
{
    int i = 0;
    int j = 0;
    int k = 0;
    while (str[i] != '\0')
    {
        while (check()->_is_space(str[i]))
            i++;
        if (str[i] == '\'')
        {
            while (str[i + 1] != '\'' && str[i] != '\0')
            {
                mini()->trimmed[k][j] = str[i];
                i++;
                if(str[i + 1] == '\'')
                {
                    break;
                }
                j++;
            }
        }
        else if (str[i] == '\"')
        {
            while (str[i + 1] != '\"' && str[i] != '\0')
            {
                mini()->trimmed[j][j] = str[i];
                i++;
                if(str[i + 1] == '\'')
                {
                    break;
                }
                j++;
            }
        }
        while (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '\0')
        {
            mini()->trimmed[k][j] = str[i];
            i++;
            j++;
        }
        mini()->trimmed[k][j] = '\0';
        j = 0;
        k++;
    }

}
