/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 20:09:10 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 15:33:13 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen((char *)str);
	while ((str[i] != (unsigned char)c) && (i > 0))
		i--;
	if (str[i] == (unsigned char)c)
		return ((char *)&str[i]);
	return (NULL);
}
