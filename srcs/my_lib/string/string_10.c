/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_10.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:49:45 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:51 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

char	*_copy_until(char *str, int n)
{
	char	*dst;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	dst = malloc(sizeof(char) * (n + 1));
	while (n-- > 0)
	{
		if (str[i] == '\0')
			break ;
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	if (i == 0)
	{
		free(dst);
		return (NULL);
	}
	return (dst);
}

int	_array_length(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	_same_word(char *w1, char *w2, int size)
{
	if (string()->_compare_n(w1, w2, size) == 0 && \
		string()->_length(w2) == size && string()->_length(w1) == size)
		return (1);
	return (0);
}

char	*_copy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*_join(char const *s1, char const *s2)
{
	size_t		i;
	size_t		j;
	char		*str;

	j = 0;
	i = -1;
	str = malloc(sizeof(char) * (string()->_length(s1) \
		+ string()->_length(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
	{
		str[i++] = s2[j++];
	}
	str[i] = '\0';
	return (str);
}
