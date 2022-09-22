#include "../includes/my_lib.h"

int	_is_alnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
