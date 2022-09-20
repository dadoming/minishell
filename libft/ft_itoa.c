/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 18:49:38 by dadoming          #+#    #+#             */
/*   Updated: 2021/12/11 15:15:33 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static int	ft_length(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (len = 1);
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static char	*ft_filler(int aux, int len, char *str)
{
	if (aux == 0)
		str[len - 1] = '0';
	if (aux < 0)
	{
		str[0] = '-';
		aux *= -1;
	}
	while (--len >= 0 && aux != 0)
	{
		str[len] = (aux % 10) + 48;
		aux = aux / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	aux;

	aux = n;
	if (aux == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_length(aux);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (ft_filler(aux, len, str));
}

// int main()
// {
// 	int a = 42;
// 	char *str = ft_itoa(a);
// 	printf("%s\n", ft_itoa(a));
// 	printf("-%c-\n", str[0]);
// 	printf("-%c-\n", str[1]);
// 	printf("-%c-\n", str[2]);
// }