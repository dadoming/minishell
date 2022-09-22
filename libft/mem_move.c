#include "../includes/my_lib.h"

void	*_mem_move(void *dst, const void *src, size_t len)
{
	unsigned char	*auxdst;
	unsigned char	*auxsrc;
	size_t			i;

	i = 0;
	auxdst = (unsigned char *)dst;
	auxsrc = (unsigned char *)src;
	if (auxdst == NULL && auxsrc == NULL)
		return (0);
	if (auxdst > auxsrc)
	{
		while (++i <= len)
			auxdst[len - i] = auxsrc[len - i];
	}
	else
	{
		while (len-- > 0)
			*auxdst++ = *auxsrc++;
	}
	return (dst);
}
