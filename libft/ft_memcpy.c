/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:38:07 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 15:26:15 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*auxdst;
	unsigned char	*auxsrc;

	auxdst = (unsigned char *)dst;
	auxsrc = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	while (n > 0)
	{
		*auxdst = *auxsrc;
		auxdst++;
		auxsrc++;
		n--;
	}
	return (dst);
}
