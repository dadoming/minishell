#include "../includes/my_lib.h"

void*	_mem_search(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*auxstr;

	auxstr = (unsigned char *)str;
	i = 0;
	while (n > 0)
	{
		if (auxstr[i] == (unsigned char)c)
			return (&auxstr[i]);
		i++;
		n--;
	}
	return (NULL);
}
