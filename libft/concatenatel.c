#include "../includes/my_lib.h"

int	_concatenatel(char *dst, const char *src, int dstsize)
{
	int	i;
	int	dst_len;

	if (dstsize <= string()->_length(dst))
		return (dstsize + ft_strlen(src));
	dst_len = string()->_length(dst);
	i = 0;
	while (src[i] != '\0' && dst_len + 1 < dstsize)
		dst[dst_len++] = src[i++];
	dst[dst_len] = '\0';
	return (string()->_length(dst) + string()->_length(&src[i]));
}
