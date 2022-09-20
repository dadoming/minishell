/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 00:45:56 by dadoming          #+#    #+#             */
/*   Updated: 2021/11/09 16:11:10 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*trim;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	len = ft_strlen((char *)s1 + i);
	while (len && (s1[len + i - 1] != 0) && ft_strchr(set, s1[len + i - 1]))
		len--;
	trim = malloc(len + 1);
	if (!trim)
		return (0);
	ft_strlcpy(trim, s1 + i, len + 1);
	trim[len] = '\0';
	return (trim);
}
