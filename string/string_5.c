#include "../includes/my_lib.h"

unsigned int _length(const char *str)
{
    unsigned int i;
	
	i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

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
