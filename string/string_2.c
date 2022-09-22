#include "../includes/my_lib.h"

int	_compare(const char *s1, const char *s2)
{
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	while ((*str1 != '\0' || *str2 != '\0'))
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}

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

int	_is_alnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
