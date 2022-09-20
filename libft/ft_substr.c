/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 21:18:49 by dadoming          #+#    #+#             */
/*   Updated: 2022/05/23 19:09:15 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*sub;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (start >= ft_strlen(str))
	{
		sub = ft_calloc(1, sizeof(char));
		if (!sub)
			return (0);
		return (sub);
	}
	if (ft_strlen(str) < len)
		return (ft_strdup(&str[i]));
	sub = ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (0);
	while (len--)
	{
		sub[i] = str[start + i];
		i++;
	}
	return (sub);
}
