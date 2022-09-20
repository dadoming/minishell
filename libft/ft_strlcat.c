/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:58:16 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 15:30:36 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	if (dstsize <= ft_strlen(dst))
		return (dstsize + ft_strlen(src));
	dst_len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && dst_len + 1 < dstsize)
		dst[dst_len++] = src[i++];
	dst[dst_len] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
