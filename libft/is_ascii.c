#include "../includes/my_lib.h"

int	_is_ascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
