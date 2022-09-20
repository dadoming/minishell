/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:07:58 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 16:01:31 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*auxdst;
	unsigned char	*auxsrc;
	size_t			i;

	i = 0;
	auxdst = (unsigned char *)dst;
	auxsrc = (unsigned char *)src;
	if (auxdst == NULL && auxsrc == NULL)
		return (0);
	if (auxdst > auxsrc)
	{
		while (++i <= len)
			auxdst[len - i] = auxsrc[len - i];
	}
	else
	{
		while (len-- > 0)
			*auxdst++ = *auxsrc++;
	}
	return (dst);
}
