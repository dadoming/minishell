/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:43:50 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:27 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

char	*_append(char **s1, char const *s2)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (_length(*s1) + _length(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[0][++i] != '\0')
	{
		str[i] = s1[0][i];
	}
	free(*s1);
	while (s2[j] != '\0')
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}

int	_atoi(const char *str)
{
	int				i;
	int				neg;
	long int		res;

	res = 0;
	neg = 1;
	i = 0;
	if (!str)
		return (0);
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res * neg) < -2147483648)
			return (0);
		if ((res * neg) > 2147483647)
			return (-1);
	}
	return ((int)res * neg);
}

void	_bzero(void *str, unsigned int n)
{
	_mem_set(str, '\0', n);
}

void	*_calloc(unsigned int count, unsigned int size)
{
	void	*c;

	c = malloc(count * size);
	if (!c)
		return (NULL);
	_mem_set(c, 0, (count * size));
	return (c);
}

int	_compare_n(const char *s1, const char *s2, unsigned int n)
{
	char	*str1;
	char	*str2;

	if (!s1 && !s2 && n == 0)
		return (0);
	if (!s1 && s2)
		return (*s2);
	if (!s2 && s1)
		return (*s1);
	str1 = (char *)s1;
	str2 = (char *)s2;
	while ((*str1 || *str2) && n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
