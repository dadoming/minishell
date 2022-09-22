#include "../includes/my_lib.h"

int	_to_upper(int letter)
{
	if (letter >= 'a' && letter <= 'z')
		letter -= 32;
	return (letter);
}
