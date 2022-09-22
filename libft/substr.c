#include "../includes/my_lib.h"

char	*_substr(const char *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	char			*new;

	if (s == NULL)
		return (NULL);
	if (len > (unsigned int)string()->_length(s))
		len = string()->_length(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	if ((unsigned int)string()->_length(s) > start)
	{
		while (i < len && s[start + i] != '\0')
		{
			new[i] = s[start + i];
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}
