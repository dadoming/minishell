#include "../includes/my_lib.h"

void	_putstring_n_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	string()->_putstring_fd(s, fd);
	string()->_putchar_fd('\n', fd);
}
