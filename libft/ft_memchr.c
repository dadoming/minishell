/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:19:20 by dadoming          #+#    #+#             */
/*   Updated: 2022/09/20 15:33:01 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*auxstr;

	auxstr = (unsigned char *)str;
	i = 0;
	while (n > 0)
	{
		if (auxstr[i] == (unsigned char)c)
			return (&auxstr[i]);
		i++;
		n--;
	}
	return (NULL);
}
