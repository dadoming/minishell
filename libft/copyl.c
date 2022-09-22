#include "../includes/my_lib.h"

int	_copyl(char *dst, const char *src, int dstsize)
{
	int	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] != '\0' && i + 1 < dstsize)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
