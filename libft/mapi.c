#include "../includes/my_lib.h"

char*	_mapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		length;
	char	*str;

	i = 0;
	if (!s || !f)
		return (0);
	length = string()->_length(s);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (0);
	while (i < length)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
