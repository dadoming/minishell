#include "../includes/my_lib.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*c;

	c = malloc(count * size);
	if (!c)
		return (NULL);
	string()->_memset(c, 0, (count * size));
	return (c);
}
