#include "../includes/my_lib.h"

int	_to_lower(int letter)
{
	if (letter >= 'A' && letter <= 'Z')
		letter += 32;
	return (letter);
}
