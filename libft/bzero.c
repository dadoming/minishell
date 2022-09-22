#include "../includes/my_lib.h"

void	_bzero(void *str, unsigned int n)
{
	string()->_memset(str, '\0', n);
}
