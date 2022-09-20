/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:00:53 by dadoming          #+#    #+#             */
/*   Updated: 2022/05/16 17:47:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>


int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	uint8_t	*str1;
	uint8_t	*str2;

	str1 = (uint8_t *)s1;
	str2 = (uint8_t *)s2;
	while ((*str1 || *str2) && n--)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (0);
}
