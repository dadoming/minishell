#include "../includes/my_lib.h"

char	*_rear_search(const char *str, char c)
{
	unsigned int	i;

	i = string()->_length(str);
	while ((str[i] != (unsigned char)c) && (i > 0))
		i--;
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (NULL);
}
