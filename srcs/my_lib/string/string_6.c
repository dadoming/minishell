#include "../../../includes/my_lib.h"


void*	_mem_search(const void *str, int c, unsigned int n)
{
	unsigned int			i;
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

void*	_mem_set(void *str, int to_swap, unsigned int len)
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

void	_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	_putnumber_fd(int n, int fd)
{
	int	a;

	if (n == -2147483648)
	{
		string()->_putstring_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		string()->_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 10)
	{
		string()->_putnumber_fd(n / 10, fd);
		string()->_putnumber_fd(n % 10, fd);
	}
	else if (n < 10)
	{
		a = (n % 10) + '0';
		string()->_putchar_fd(a, fd);
	}
}

void	_putstring_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		string()->_putchar_fd(s[i], fd);
		i++;
	}
}
