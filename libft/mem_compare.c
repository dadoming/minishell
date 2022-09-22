#include "../includes/my_lib.h"

int	_mem_compare(const void *s1, const void *s2, size_t n)
{
	unsigned char	*auxstr1;
	unsigned char	*auxstr2;
	size_t			i;

	if (!n)
		return (0);
	auxstr1 = (unsigned char *)s1;
	auxstr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (auxstr1[i] != auxstr2[i])
			return (auxstr1[i] - auxstr2[i]);
		i++;
	}
	return (0);
}
