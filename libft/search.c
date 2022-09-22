#include "../includes/my_lib.h"

char*	_search(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != (unsigned char) c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&str[i]);
}
