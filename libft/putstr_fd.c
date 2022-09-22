#include "../includes/my_lib.h"

void	_putstring_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		string()->_putchar_fd(s[i], fd);
		i++;
	}
}
