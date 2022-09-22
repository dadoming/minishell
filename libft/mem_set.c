#include "../includes/my_lib.h"

void	*_mem_set(void *str, int to_swap, unsigned int len)
{
	unsigned char	*aux;

	aux = (unsigned char *)str;
	while (len > 0)
	{
		*aux = to_swap;
		aux++;
		len--;
	}
	return (str);
}
