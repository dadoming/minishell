/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:36:27 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 16:00:33 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*auxstr1;
	unsigned char	*auxstr2;
	size_t			i;

	if (!n)
		return (0);
	auxstr1 = (unsigned char *)s1;
	auxstr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (auxstr1[i] != auxstr2[i])
			return (auxstr1[i] - auxstr2[i]);
		i++;
	}
	return (0);
}
