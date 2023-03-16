#include "../../includes/minishell.h"

static char	*copy_until(char *str, int n)
{
	char	*dst;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	dst = malloc(sizeof(char) * (n + 1 + 1));
	if (!dst)
		return (NULL);
	dst[0] = '$';
	while (n-- > 0)
	{
		dst[i + 1] = str[i];
		i++;
	}
	dst[i + 1] = '\0';
	return (dst);
}

char *get_word(char *content, int i)
{
    int end;
    char *word;

    end = i + 1;
    word = NULL;
    while (check()->_is_space(content[end]) == 0 && content[end] != '\0' && \
            (check()->_is_alnum(content[end]) == 1 || content[end] == '_'))
    {
        end++;
    }
    word = _copy_until(&content[i], end - i);
    return (word);
}

static void remove_found(int *i, char *content, int *quote)
{
    int end;

    end = *i + 1;
    while (check()->_is_space(content[end]) == 0 && content[end] != '\0' && \
        (check()->_is_alnum(content[end]) == 1 || content[end] == '_'))
        end++;
    remove_word(content, *i, end);
    *i = -1;
    *quote = NO_QUOTE;
}

static void find_in_env(int *found, t_shell *mini, char *word)
{
    int j;
    int env_len;
    char *env_variable;
    
    j = 0;
    while (mini->core->env_p[j] != 0)
    {
        env_len = string()->_length_until_c(mini->core->env_p[j], '=');
        env_variable = copy_until(mini->core->env_p[j], env_len);
        if (string()->_compare_n(env_variable, word, string()->_length(word)) == 0 && \
            string()->_length(env_variable) == string()->_length(word))
        {
            *found = 1;
            free(env_variable);
            break;
        }
        free(env_variable);
        env_variable = NULL;
        j++;
    }
}

char *remove_non_existent(t_shell *mini, char *content, int quote)
{
    int i; 
    int found;
    char *word;
    
    word = NULL;
    i = -1;
    while (content[++i] != '\0')
    {
        if (content[i] == '\'' || content[i] == '\"')
        {
            check_quote(&quote, content[i]);
            if (quote == SINGLE_QUOTE)
                continue;
        }
        if (content[i] == '$' && (quote == NO_QUOTE || quote == DOUBLE_QUOTE))
        {
            word = get_word(content, i);
            found = 0;
            find_in_env(&found, mini, word);
            if (found == 0)
                remove_found(&i, content, &quote);
            else if (found == 1)
                i += string()->_length(word) - 1;
            free(word);
        }
    }
    return (content);
}