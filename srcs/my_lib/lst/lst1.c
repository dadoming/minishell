/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 00:41:53 by dadoming          #+#    #+#             */
/*   Updated: 2023/03/17 13:12:14 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_lib.h"

t_list	*_new_node(void *token)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new -> token = token;
	new -> next = NULL;
	return (new);
}

int	_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}

t_list	*_last(t_list *lst)
{
	if (lst == NULL)
		return (0);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
	}
	return (lst);
}

void	_add_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new -> next = *lst;
	*lst = new;
}

void	_add_back(t_list **lst, void *content)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = list()->_new_node(content);
		return ;
	}
	list()->_last(*lst)->next = list()->_new_node(content);
}
