#include "../includes/my_lib.h"

void	_putnumber_fd(int n, int fd)
{
	int	a;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (n < 10)
	{
		a = (n % 10) + '0';
		ft_putchar_fd(a, fd);
	}
}
