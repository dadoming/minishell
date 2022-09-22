#include "../includes/my_lib.h"

char	*_strnstr(const char *str, const char *to_find, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	j = 0;
	n = string()->_length(to_find);
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && ((i + j) < len))
		{
			if (j == n - 1)
				return ((char *)&str[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}
