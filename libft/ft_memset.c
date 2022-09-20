/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:17:56 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 15:27:33 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int to_swap, size_t len)
{
	unsigned char	*aux;

	aux = (unsigned char *)str;
	while (len > 0)
	{
		*aux = to_swap;
		aux++;
		len--;
	}
	return (str);
}
