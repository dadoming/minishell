#include "../includes/my_lib.h"

void	_putstring_n_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	string()->_putstring_fd(s, fd);
	string()->_putchar_fd('\n', fd);
}

char	*_rear_search(const char *str, char c)
{
	unsigned int	i;

	i = string()->_length(str);
	while ((str[i] != (unsigned char)c) && (i > 0))
		i--;
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (NULL);
}

char*	_search(const char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != (unsigned char) c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&str[i]);
}

char	*_strnstr(const char *str, const char *to_find, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	n;

	i = 0;
	j = 0;
	n = string()->_length(to_find);
	if (*to_find == '\0')
		return ((char *)str);
	while (str[i] != '\0')
	{
		while (str[i + j] == to_find[j] && ((i + j) < len))
		{
			if (j == n - 1)
				return ((char *)&str[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}

char	*_substr(const char *s, unsigned int start, unsigned int len)
{
	unsigned int	i;
	char			*new;

	if (s == NULL)
		return (NULL);
	if (len > (unsigned int)string()->_length(s))
		len = string()->_length(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	if ((unsigned int)string()->_length(s) > start)
	{
		while (i < len && s[start + i] != '\0')
		{
			new[i] = s[start + i];
			i++;
		}
	}
	new[i] = '\0';
	return (new);
}
