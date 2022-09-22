#include "../includes/my_lib.h"

int	_is_printable(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
