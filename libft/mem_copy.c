#include "../includes/my_lib.h"

void	*_mem_copy(void *dst, const void *src, size_t n)
{
	unsigned char	*auxdst;
	unsigned char	*auxsrc;

	auxdst = (unsigned char *)dst;
	auxsrc = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	while (n > 0)
	{
		*auxdst = *auxsrc;
		auxdst++;
		auxsrc++;
		n--;
	}
	return (dst);
}
