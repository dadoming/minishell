#include "../includes/my_lib.h"

void	_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
