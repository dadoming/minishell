#include "../includes/my_lib.h"

int	_atoi(const char *str)
{
	int				i;
	int				neg;
	long int		res;

	res = 0;
	neg = 1;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res * neg) < -2147483648)
			return (0);
		if ((res * neg) > 2147483647)
			return (-1);
	}
	return ((int)res * neg);
}
