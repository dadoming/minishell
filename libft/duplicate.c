#include "../includes/my_lib.h"

char	*_duplicate(const char *str)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc((1 + string()->_length(str)) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
